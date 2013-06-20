<div id="solutions_news">
<h3><div class="rightlink"><a class="twitter-icon-solutions" target="_blank" href="http://twitter.com/SAICEngineering">Follow Us on Twitter</a><!-- &nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;<a href="http://investors.saic.com/phoenix.zhtml?c=193857&p=irol-news&nyo=0">View All News &raquo;</a> --></div>
News &amp; Events</h3>
  <ul>
    <?php foreach($tweets as $tweet) { ?>
      <li><a href="<?php print $tweet['link']; ?>"><?php print $tweet['body']; ?> <br><div class="date"><?php print $tweet['days_since']; ?></div></a></li>
    <? } ?>
  </ul>
</div>
