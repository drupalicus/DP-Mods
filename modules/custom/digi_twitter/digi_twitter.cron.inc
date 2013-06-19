<?php

function digi_twitter_cron_helper() {
  // Get a list of all the twitter feeds
  $twitter_feeds = db_query("SELECT n.nid AS twitter_feed_nid, n.title AS twitter_feed_title, cttf.field_twitter_feed_alias_value AS twitter_username, n.language FROM {node} n JOIN {content_type_twitter_feed} cttf ON n.nid = cttf.nid AND n.vid = cttf.vid WHERE n.type = 'twitter_feed' AND n.status = 1");

  // Iterate through the list of feeds
  while($feed = db_fetch_array($twitter_feeds)) {
    // Get the feed
    $url = "http://twitter.com/statuses/user_timeline/".$feed['twitter_username'].".rss";

    $ch = curl_init();    // initialize curl handle
    curl_setopt($ch, CURLOPT_URL,$url); // set url to post to
    curl_setopt($ch, CURLOPT_FAILONERROR, 1);
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 1);// allow redirects
    curl_setopt($ch, CURLOPT_RETURNTRANSFER,1); // return into a variable
    curl_setopt($ch, CURLOPT_TIMEOUT, 5); // times out after 5s
    $result = curl_exec($ch); // run the curl request
    curl_close($ch);

   try {
      $xml = new SimpleXMLElement($result);
      // Process the feed
      foreach($xml->channel->item as $tweet) {
        $username = $feed['twitter_username'];
        $description = trim(strstr($tweet->description, ' '));

        if (preg_match_all('/(#\w+)/', $tweet->description, $matches)) {
          $tags = implode(', ', preg_replace('/#/', '', $matches[0]));
        }
        else{
          $tags = '';
        }

        $published_date = strtotime($tweet->pubDate);
        $guid = $tweet->guid;

        _twitter_process_tweet((string)$feed['twitter_feed_nid'], (string)$feed['twitter_feed_title'], (string)$feed['language'], (string)$username, (string)$description, $tags, $published_date, (string)$guid);
      }
    } catch (Exception $e) {
      watchdog('twitter', "Failed getting tweets for {$feed['twitter_username']}." . $e->getMessage(), array(), WATCHDOG_ERROR);
    }
  }
}

function _twitter_process_tweet($feed_nid, $feed_title, $feed_lang, $username, $tweet, $tags, $published_date, $guid) {
  static $format_id = -1;

  if ($format_id < 0) {
    $formats = filter_formats();
    foreach($formats as $id => $value) {
      if ($value->name == "Full HTML") {
        $format_id = $id;
        break;
      }
    }
  }


  // Run a check to see if there's an existing node for this event.
  $query = 'SELECT nid FROM {content_type_tweet} WHERE field_tweet_guid_value = "%s"';
  $result = db_fetch_array(db_query($query, (string)$guid));

  $create = false;
  $update = false;
  $delete = false;
  $previously_draft = false;

  if($result === false){
    // No existing node.  Prep a new node object and execute the form to create one.
    $node = array(
      'uid' => (string)$user->uid,
      'name' => (string)$user->name,
      'type' => 'tweet',
      'language' => $feed_lang,
      'body' => NULL,
      'title' => NULL,
      'format' => NULL,
      'status' => true,
      'promote' => false,
      'sticky' => false,
      'created' => time(),
      'revision' => false,
      'comment' => '0',
    );

    $node = (object)$node;

    $create = true;
    $create_counter++;

    module_load_include('inc', 'node', 'node.pages');

    $node->title = (string)str_replace("\n", ' ', $tweet);
    $node->body = (string)$tweet;
    $node->format = $format_id;
    $node->uid = $user->uid;
    $node->name = $user->name;
    $node->field_tweet_published_date = array(
      array(
        'value' => date('c', $published_date),
        'timezone' => 'UTC',
        'timezone_db' => 'UTC',
        'date_type' => 'date'
      )
    );
    $node->field_tweet_source = array(array('nid' => (string)$feed_nid));
    $node->field_tweet_guid = array(array('value' => $guid));
    if ($vocabs = taxonomy_get_vocabularies('tweet')) {
      foreach($vocabs as $vocab) {
        if ($vocab->name == 'Tweet Hashtags') {
          $node->taxonomy['tags'][$vocab->vid] = $tags;
          break;
        }
      }
    }

    $node = node_submit($node);
    node_save($node);
  }
}
