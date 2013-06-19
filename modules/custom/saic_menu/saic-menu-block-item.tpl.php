<li class="<?php print $classes; ?>">
  <a href="<?php print url($branch['link_path']); ?>" title="<?php print $branch['link_title']; ?>" class="<?php print $link_classes; ?>">
  <?php
  if ($config['menu_delta'] == 'topnav') {
    print '</a>';
  	print $submenu;
  }
  else {
  	print '<div class="menu-container"></div>';
  	print $branch['title'];
    print '</a>';
  }
  if (!empty($content)) {
  	print '<ul id="mainnav">' . $content . '</ul>';
  }
  ?>
</li>