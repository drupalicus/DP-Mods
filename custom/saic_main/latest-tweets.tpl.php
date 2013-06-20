<div id="twitter_div" class="box">
  <a target="_blank" href="http://twitter.com/SAICinc"><h3>Twitter Updates</h3></a>   
	<ul id="twitter_update_list" class="underheading">
    <?php foreach ($tweets as $index => $tweet) { ?>
      <li><span><?php print t($tweet['body']); ?></span></li>
    <? } ?>
  </ul>
  <p class="actionlink"><a href="http://twitter.com/SAICinc">Follow SAIC on Twitter »</a></p>
</div>
