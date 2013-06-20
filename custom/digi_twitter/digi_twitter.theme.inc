<?php

function theme_digi_twitter_tweet_body_link($body = '') {
  $content = array();
  preg_match_all('!https?://[\S]+!', $body, $matches);
  if(!empty($matches[0][0])) {
    $content['link'] = $matches[0][0];
    $content['body'] = str_replace ($content['link'],'',$body);
  }

  return $content;
}


/**
 * theme functions
 * TODO: When changing urls all changes should be done here
 */
function theme_digi_twitter_topics_link($row) {
  if ($_GET['q'] == 'twitter/tags/' . $row['name']) {
    $link_class = 'active';
  }

  $url_safe_name = $row['name'];

  $content = '<li>' . l('#' . $row['name'], 'twitter/tags/' . $url_safe_name, array('attributes' => array('class' => $link_class))) . '</li>';
  return $content;
}

function theme_digi_twitter_contributor_link($row) {
  $display_name = digi_twitter_get_display_name($row['field_twitter_feed_alias_value'], $row['field_twitter_feed_formal_name_value'], $row['author']->full_display_name);
  if ($_GET['q'] == 'twitter/contributors/' . $row['field_twitter_feed_alias_value']) {
    $link_class = 'active';
  }
  $content = '<li>' . l($display_name, 'twitter/contributors/' . $row['field_twitter_feed_alias_value'], array('attributes' => array('class' => $link_class))) . '</li>';
  return $content;
}

function theme_digi_twitter_contributor_detail_link($row) {
  $display_name = digi_twitter_get_display_name($row['field_twitter_feed_alias_value'], $row['field_twitter_feed_formal_name_value'], $row['author']->full_display_name);
  $image = digi_twitter_get_avatar_image('twitter_avatar', $row['field_twitter_feed_avatar_fid'], $row['author'], $display_name);

  $content .= '<li class="twitter-contributor clearfix">
            <div class="image">' .$image .'</div>
            <div class="content">
              <div class="twitter-contributor-links">' .
              l($display_name, 'twitter/contributors/' . $row['field_twitter_feed_alias_value']) .
              '<span class="twitter-contributor-external">
                <a href="http://www.twitter.com/' . $row['field_twitter_feed_alias_value'] . '" class="external">
                  @' . $row['field_twitter_feed_alias_value'] . '
                </a>
              </span>
              </div>
            </div> <!-- .content -->
          </li>';
  return $content;
}

function theme_digi_twitter_archive_link($row) {
  if ($_GET['q'] == 'twitter/archives/' . $row['year']) {
    $link_class = 'active';
  }
  $content = '<li>' . l(t($row['month_name']) . ' ' . $row['year'], 'twitter/archives/' . $row['year'], array('attributes' => array('class' => $link_class))) . '</li>';
  return $content;
}

function theme_digi_twitter_archive_details_link($row) {
  $content = '<li>' . l(t($row['month_name']), 'twitter/archives/' . $row['year'] . '/' . $row['month']) . ' (' . $row['count'] . ')</li>';
  return $content;
}

function theme_digi_twitter_contributor_header($twitter_feed, $author) {

  $image = digi_twitter_get_avatar_image('twitter_author_thumbnail', $twitter_feed->field_twitter_feed_avatar[0], $author, $twitter_feed->title);

  $follow_link = '<a href="http://www.twitter.com/' . $twitter_feed->field_twitter_feed_alias[0]['value'] . '" class="generic-simple-button more"><span>Follow @' . $twitter_feed->field_twitter_feed_alias[0]['value'] . '</span></a>';

  $display_name = digi_twitter_get_display_name($twitter_feed->field_twitter_feed_alias[0]['value'], $twitter_feed->field_twitter_feed_formal_name[0]['value'], $author->full_display_name);

  //TODO: this is commented out until we implement the user bio page
  if (!empty($author->body) && ($author->field_disabled[0]['value'] != 1)) {
    $bio_link = '<a href="' . url("node/" . $author->nid) . '" class="generic-simple-button more"><span>Biography</span></a>';
    $title_links = l($display_name, 'node/' . $author->nid);
    $image = '<a href="' . url("node/" . $author->nid) . '">' . $image . '</a>';
  }
  else {
    $bio_link = '';
    $title_links = $display_name;
  }

  $title_dept = $author->field_person_title[0]['value'];
  if (!empty($title_dept) && !empty($author->field_person_department[0]['value'])) {
    $title_dept .= ', ';
  }
  $title_dept .= $author->field_person_department[0]['value'];

  $content = '<!-- Start: Twitter Filter Details -->
      <div class="filter-details filter-details-with-image">' .
        $image .
        '<div class="filter-back"><a href="/twitter">Back To All Tweets</a></div>
        <div class="filter-author-name"><h1>' . $title_links . '</h1></div>
        <div class="filter-author-title">' . $title_dept. '</div>
        <div class="filter-author-buttons generic-simple-button-holder">' .
          $bio_link . $follow_link .
        '</div>
      </div>
      <!-- End: Twitter Filter Details -->';

  return $content;
}

/**
 * create list of 3 tweets that is related to content on the page
 *
 * @param $type - type of relation. allowed values are 'hashtag', 'author', null
 * @param $arg - value used for the relation
 * @param $title - the title of the section
 * @param $do_backfill - if this is true, show latest tweets without applying filter, if false, show nothing if there are no tweets
 */
function theme_digi_twitter_related_tweets($type = NULL, $arg = NULL, $title = NULL, $do_backfill = TRUE, $accordion = FALSE) {

  if ($type == 'author') {
    $view_all_url = '/twitter/contributors/' . $arg;
    $view_display = 'block_1';
  }
  elseif ($type == 'hashtag') {
    $view_all_url = '/twitter/tags/' . $arg;
    $view_display = 'block_2';
  }
  else {
    $view_all_url = '/twitter';
    $view_display = 'block_1';
  }

  $view = views_get_view('tweets');
  $latest_tweets = $view->execute_display($view_display, array($arg));
  $content = $latest_tweets['content'];

  //try to load generic tweets if specific type loaded nothing
  if ($content == '' && $type != null && $do_backfill == true) {
    $view_all_url = '/twitter';

    $view = views_get_view('tweets');
    $latest_tweets = $view->execute_display('block_1');
    $content = $latest_tweets['content'];
  }

  if ($content != '') {
    $content = '
                <div class="menu-section' . ($accordion ? ' expand-container' : '') . '" id="menu-section-tweets">
               ' . ($accordion ? '<div class="expand">' : '') . '
                  <ul>' . $content . '</ul>
                  <div class="generic-simple-button-holder">
                    <a class="generic-simple-button more" href="' . $view_all_url . '"><span>View All</span></a>
                  </div>
               ' . ($accordion ? '</div>' : '') . '
                </div>';
  }
  return $content;
}

function theme_digi_twitter_tweet_body($body = '') {
  $result = _filter_url($body, -1);
  $result = digi_twitter_link_filter($result);
  $result = digi_twitter_link_filter($result, '#', 'http://search.twitter.com/search?q=%23');
  return preg_replace('/<a href/', '<a target="_blank" href', $result);
}

function theme_digi_twitter_tout($args = null) {
  if (is_array($args) && $args['image']) {
    return '
    <div
      class="digi_twitter_tout"
      onclick="location.href=\''.$args['link'].'\'"
      style="background: transparent url(\'/'.$args['image'].'\') 0 0 no-repeat">
    </div>';
  } else {
    return '';
  }
}

// taken from the twitter project - Thank you!
// slightly modified to put the '@' outside of the link as twitter is doing it now.
function digi_twitter_link_filter($text, $prefix = '@', $destination = 'http://twitter.com/') {
  $matches = array(
    '/\>' . $prefix . '([a-z0-9_]{0,15})/i',
    '/^' . $prefix . '([a-z0-9_]{0,15})/i',
    '/(\s+)' . $prefix . '([a-z0-9_]{0,15})/i',
  );
  if ($prefix == '@') {
    $replacements = array(
      '>' . $prefix . '<a href="' . $destination . '${1}">${1}</a>',
      $prefix . '<a href="' . $destination . '${1}">${1}</a>',
      '${1}' . $prefix . '<a href="' . $destination . '${2}">${2}</a>',
    );
  } else {
    $replacements = array(
      '><a href="' . $destination . '${1}">' . $prefix . '${1}</a>',
      '<a href="' . $destination . '${1}">' . $prefix . '${1}</a>',
      '${1}<a href="' . $destination . '${2}">' . $prefix . '${2}</a>',
    );
  }
  return preg_replace($matches, $replacements, $text);
}
