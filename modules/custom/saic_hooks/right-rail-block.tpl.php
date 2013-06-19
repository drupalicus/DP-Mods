<?php 
  $first_class = '';
  if($id == 1){
    $first_class = 'menu-filter-set-first';
  }
?>
<div class="menu-filter-set <?php print $first_class;?>">

  <h3><?php print $title; ?></h3>
  <ul>
    <?php print $content; ?>
  </ul>

  <?php if($show_more){?>
	<div class="generic-simple-button-holder">
	  <a href="#" class="generic-simple-button" id="<?php print $link_id; ?>"><span><?php print t('see full list');?></span></a>
	</div>
  <?php } ?>
</div>
