<?php print theme('imagecache', 'magazine_article_thumb', $node->field_magazine_article_image[0]['filepath'], $node->field_magazine_article_image[0]['data']['alt'], '', array('class'=>'promo featured_image_border')); ?>     

<div class="content_left">
  <div class="kicker2"><?php print $node->field_magazine_article_issue_node->title; ?></div>
  <h1><?php print $node->title; ?></h1>
  <h2><?php print $node->field_magazine_article_teaser[0]['value']; ?></h2>
</div>
<hr />

