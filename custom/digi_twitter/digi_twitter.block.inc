<?php

/**
 * list 5 topics with the most tweets in a block
 */
function digi_twitter_block_topics() {
  $content = qualcomm_hooks_right_rail_topics_block_content('tweet', 'digi_twitter_topics_link', 'twitter-view-all-topics', 6);
  return $content;
}

/**
* links to social media
* TODO: We need these urls
*/
function digi_twitter_block_join() {
    $content = '<div class="menu-section" id="menu-section-conversations">
                <h3 class="menu-section-title">Join Our Conversations</h3>
                 <ul>
            <li class="menu-conv-blog"><a href="/blog" title="OnQ Blog">OnQ Blog</a></li>
                  <li class="menu-conv-twitter"><a href="/twitter" title="Qualcomm Tweets">Twitter</a></li>
                  <li class="menu-conv-youtube"><a title="Visit Qualcomm on YouTube" href="http://www.youtube.com/QUALCOMMVlog" target="_blank">YouTube</a></li>
                  <li class="menu-conv-facebook"><a title="Visit Qualcomm on Facebook" href="http://www.facebook.com/qualcomm" target="_blank">Facebook</a></li>
                  <li class="menu-conv-linkedin"><a title="Visit Qualcomm on LinkedIn" href="http://www.linkedin.com/companies/qualcomm" target="_blank">LinkedIn</a></li>
                </ul>
                </div>';

  return $content;
}

/**
 * list 5 contributors with the most tweets in a block
 */
function digi_twitter_block_contributors() {

  $lang = i18n_get_lang();

  $cache = cache_get('digi_twitter_block_contributors:' . $lang, 'cache_block');
  if (!empty($cache) && !empty($cache->data)) {
    $content = $cache->data;
    return $content;
  }

  $query = "select tf.nid, tf.field_twitter_feed_alias_value, tf.field_twitter_feed_formal_name_value,
              tf.field_twitter_feed_avatar_fid, tf.field_twitter_feed_author_nid, count(ntw.nid) as 'count'
            from {node} n
            join {content_type_twitter_feed} tf on tf.vid = n.vid
            left join {content_type_tweet} t on t.field_tweet_source_nid = n.nid
            left join {node} ntw on ntw.vid = t.vid
            where n.type = 'twitter_feed'
            and n.status <> 0
            and ntw.status <> 0
            and n.language = '" . $lang . "'
            group by tf.nid, tf.field_twitter_feed_alias_value, tf.field_twitter_feed_formal_name_value,
              tf.field_twitter_feed_avatar_fid, tf.field_twitter_feed_author_nid
            order by coalesce(field_twitter_feed_weight_value, 0), count(ntw.nid) desc;
            ";

  $result = db_query($query);
  $rows = digitaria_uitlity_get_dbresult_as_array($result);

  //theme rows
  $link_html = '';
  for($x = 0; $x < 5 && $x < count($rows); $x++) {
    //load author object
    $rows[$x]['author'] = node_load($rows[$x]['field_twitter_feed_author_nid']);
    $link_html .= theme('digi_twitter_contributor_detail_link', $rows[$x]);
  }

  $show_more = false;
  if (count($rows) > 5) {
    $show_more = true;
  }

  $content = theme('right_rail_block', t('Contributors'),  $link_html, 'twitter-view-all-contributors', $show_more);

  //theme modal popup
  usort($rows, '_digi_twitter_sort_tweeter');
  $modal_content .= digitaria_uitlity_split_array_to_ul($rows, 4, 'digi_twitter_contributor_link');
  $content .= theme('modal_popup', 'contributor', t('Contributors'), $modal_content);

  cache_set('digi_twitter_block_contributors:' . $lang, $content, 'cache_block');

  return $content;
}

/**
 * list 5 most recent months with the most tweets in a block
 */
function digi_twitter_block_archive() {
  $lang = i18n_get_lang();

  $cache = cache_get('digi_twitter_block_archive:' . $lang, 'cache_block');
  if (!empty($cache) && !empty($cache->data)) {
    $content = $cache->data;
    return $content;
  }

  $query = "SELECT date_format(from_unixtime(n.created), '%M') AS 'month_name',
              DATE_FORMAT(from_unixtime(n.created), '%m') AS 'month',
              DATE_FORMAT(from_unixtime(n.created), '%Y') AS 'year',
              COUNT(distinct n.nid) AS 'count'
            FROM {node} AS n
            JOIN content_type_tweet t ON t.vid = n.vid
            JOIN content_type_twitter_feed f ON f.nid = t.field_tweet_source_nid
            JOIN node fn ON fn.vid = f.vid
            WHERE n.status <> 0
            AND n.type = 'tweet'
            AND n.language = '" . $lang . "'
            AND fn.language = '" . $lang . "'
            GROUP BY year, month
            ORDER BY year DESC, month DESC";
  $result = db_query($query);
  $rows = digitaria_uitlity_get_dbresult_as_array($result);

  //theme rows
  $link_html = '';
  for($x = 0; $x < 5 && $x < count($rows); $x++) {
    $link_html .= theme('digi_twitter_archive_details_link', $rows[$x]);
  }

  $show_more = false;
  if (count($rows) > 5) {
    $show_more = true;
  }

  $content = theme('right_rail_block', t('Archive'),  $link_html, 'twitter-view-all-archives', $show_more);

  //theme modal popup
  $modal_content .= digitaria_uitlity_split_array_to_ul($rows, 4, 'digi_twitter_archive_link');
  $content .= theme('modal_popup', 'archive', t('Archive'), $modal_content);

  cache_set('digi_twitter_block_archive:' . $lang, $content, 'cache_block');

  return $content;
}

/**
 * header block for contributor page
 */
function digi_twitter_block_contributor_header() {
  $content = '';

  if (arg(0) == 'twitter' && arg(1) == 'contributors' && arg(2) != '') {

    $twitter_feed = _digi_twitter_get_feed_from_alias(arg(2));

    if (!empty($twitter_feed)) {
      $author = node_load($twitter_feed->field_twitter_feed_author[0]['nid']);

      $content = theme('digi_twitter_contributor_header', $twitter_feed, $author);

    }
  }

  return $content;
}

/**
 * Block callback for the 3 most recent tweets
 */
function digi_twitter_block_latest_tweets(){
  $view = views_get_view('tweets');
  $view->set_display('page_1');
  $view->execute();

  $link_html = '';
  for($x = 0; $x < count($view->result) && $x < 3; $x++) {
    $result = $view->result[$x];

    $nid = $result->nid;
    $timestamp = strtotime($result->node_data_field_tweet_published_date_field_tweet_published_date_value);
    $username = $result->node_node_data_field_tweet_source_node_data_field_twitter_feed_avatar_field_twitter_feed_alias_value;
    $description = theme('digi_twitter_tweet_body', $result->node_revisions_body);

    $date =  digitaria_utility_format_date_translate($timestamp, $format = 'M j');
    $time = date('g:ia', $timestamp);

    $li_class = 'no-image';
    $li_class .= ($x == 0) ? ' first' : '';
    $li_class .= ($x + 1 == min(count($view->result), 3)) ? ' last' : '';

    $link_html .= theme('node_tweet_teaser', $username, $description, $date, $time, NULL, $li_class);
  }

  $content = theme('right_rail_block', t('Recent Tweets'), $link_html, 'content-list-tweet', TRUE, t('view all'), '/twitter', 'content-list-tweet');

  return $content;

}

/**
 * hook_block callback for Tweets Related by tag
 */
function digi_twitter_block_related_by_tag() {
  $term_ids = qualcomm_util_get_related_by_tags_tids();
  $content = '';
  if(!empty($term_ids)){

    $view = views_get_view('related_content');
    $view->set_display('block_3');
    $view->set_arguments(array($term_ids));
    $view->execute();

    $link_html = '';
    if (!empty($view->result)) {
      foreach ($view->result as $x => $result) {
        $nid = $result->nid;
        $timestamp = strtotime($result->node_data_field_tweet_published_date_field_tweet_published_date_value);
        $username = $result->node_node_data_field_tweet_source_node_data_field_twitter_feed_alias_field_twitter_feed_alias_value;
        $description = theme('digi_twitter_tweet_body', $result->node_revisions_body);

        $date =  digitaria_utility_format_date_translate($timestamp, $format = 'M j');
        $time = date('g:ia', $timestamp);

        $li_class = 'no-image';
        $li_class .= ($x == 0) ? ' first' : '';
        $li_class .= ($x + 1 == min(count($view->result), 3)) ? ' last' : '';

        $link_html .= theme('node_tweet_teaser', $username, $description, $date, $time, NULL, $li_class);
      }
    }
  }
  $more_url = qualcomm_util_get_related_by_tags_view_more($term_ids, '/twitter', '/twitter/tags/');
  $content = theme('right_rail_block', t('Related Tweets'), $link_html, 'content-list-related-tweet', TRUE, t('view all'), $more_url, 'content-list-related-tweet');

  return $content;
}

/**
 *  sort function for tweet author
 */
function _digi_twitter_sort_tweeter($a, $b) {
  $a['display_name'] = digi_twitter_get_display_name($a['field_twitter_feed_alias_value'], $a['field_twitter_feed_formal_name_value'], $a['author']->title);
  $b['display_name'] = digi_twitter_get_display_name($b['field_twitter_feed_alias_value'], $b['field_twitter_feed_formal_name_value'], $b['author']->title);
  return strcasecmp($a['display_name'], $b['display_name']);
}
