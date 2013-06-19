<?php
  $created_time = strtotime($created);
  if (!empty($nid)) {
    $date_link = l(date('g:ia M j', $created_time), 'node/' . $nid);
  }
  else {
    $date_link = date('g:ia M j', $created_time);
  }
?>
<div class="content">
  <a href="/twitter/contributors/<?php print $username; ?>" class="twitter-post-author"><?php print $username; ?></a>
  <span class="twitter-post-content">
      <?php print theme('digi_twitter_tweet_body', $body) ?>&nbsp;
  </span>

  <div class="meta twitter-post-meta">
    <span class="time twitter-post-time"><?php print $date_link; ?></span>
    <ul class="twitter-post-controls generic-simple-button-holder hide">
      <li>
        <a target="_blank" href="http://twitter.com/home/?status=<?php print urlencode('@' . $username); ?>" class="generic-simple-button"><span><?php print t('reply'); ?></span></a>
      </li>
      <li>
        <a target="_blank" href="http://twitter.com/home/?status=<?php print urlencode('RT @' . $username . ' ' . trim($body)) ?>" class="generic-simple-button"><span><?php print t('retweet');?></span></a>
      </li>
    </ul>
  </div>
</div>
