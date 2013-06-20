<?php if ($node->field_story_image[0]['filepath']): ?>
<img class="promo" style="border: 1px solid #BEBEBE; padding: 3px;" alt="<?php print $node->field_story_image[0]['data']['alt']; ?>" src="/<?php print $node->field_story_image[0]['filepath']; ?>">
<?php endif ?>
<div class="content_left">
<?php if ($node->title): ?>
  <h1><?php print $node->title; ?></h1>
<?php endif ?>
<?php if ($node->field_story_sub_title[0]['value']): ?>
  <h2><?php print $node->field_story_sub_title[0]['value']; ?></h2>
<?php endif ?>
</div>
<hr clear="all">
