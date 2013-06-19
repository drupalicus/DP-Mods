<?php print theme('imagecache', 'resource_thumb', $node->field_resource_image[0]['filepath'], $node->field_resource_image[0]['data']['alt'], '', array('class'=>'promo  featured_image_border')); ?>
<div class="content_left">
  <h1><?php print $node->title ?></h1>
  <h2><?php print $node->field_resource_teaser[0]['value']; ?></h2>
</div>
<hr>
