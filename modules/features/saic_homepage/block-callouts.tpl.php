<div id="subpromos" class="clearfix">
  <?php 
  $count = 1;
  foreach($callouts as $index => $data) { ?>
	  <div>
      <a href="<?php print $data['url'] ?>">
        <img <?php if(count($callouts) == $count ) echo 'class="last"'; ?> src="/<?php print $data['file_name'] ?>" />
      </a>
    </div>
  <?php  $count++; } ?>
</div>
<br class="clear" />
