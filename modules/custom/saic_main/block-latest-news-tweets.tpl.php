<div class="news_events">
  <div class="morenews"><a class="twitter-icon-solutions" target="_blank" href="http://twitter.com/SAICEngineering">Follow Us on Twitter</a></div> 
  <h3>News and Events</h3>
  <ul>
    <?php foreach($tweets as $tweet) { ?>
      <li><a href="<?php print $tweet['link']; ?>"><span><?php print $tweet['body']; ?></span> <br><div class="date"><?php print $tweet['days_since']; ?></div></a></li>
    <? } ?>
  </ul>
</div>

