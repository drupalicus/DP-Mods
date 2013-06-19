<div id="ticker">
  <a href="ttp://investors.saic.com/phoenix.zhtml?c=193857&p=rssSubscription"><img src="/images/rss_icon.gif" class="rssicon-home" width="16" height="16" alt="RSS Icon" /></a>
  <h3><a href="http://investors.saic.com/phoenix.zhtml?c=193857&p=irol-news">Latest SAIC News:</a></h3>
	<div class="news">
    <?php foreach($tweets as $index => $data ) { ?>
	    <a href="<?php print $data['link'] ?>"><?php print $data['body'] ?></a>
    <?php } ?>
	</div>
</div>
