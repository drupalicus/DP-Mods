<?php 
if($config['menu_delta'] == 'primary-links')
  $section = 'section';
else if($config['menu_delta'] == 'featured-links')
  $section = 'solutions_nav';
else
  $section = 'nav';
?>
<ul id="<?php print $section ?>">
  <?php print $content; ?>
</ul>
