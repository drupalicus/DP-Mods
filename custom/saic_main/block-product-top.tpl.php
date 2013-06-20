<?php if ($node->field_product_image[0]['filepath']): ?>
<?php print theme('imagecache', 'product_thumb', $node->field_product_image[0]['filepath'], $node->field_product_image[0]['data']['alt'], $node->title, array('class' => 'promo')); ?>
<?php endif ?>
<div class="content_left">
<?php if ($node->title): ?>
  <h1><?php print $node->title; ?></h1>
<?php endif ?>
<?php if ($node->field_product_teaser[0]['value']): ?>
  <h2><?php print $node->field_product_teaser[0]['value']; ?></h2>
<?php endif ?>

  <div class="contact_interested">
    <a href="/tools/contact"><input border="0" type="image" alt="Interested? Contact Us Today" src="/sites/all/themes/saic/images/btn_interestedcontactus.gif" name="submit"></a>
  </div>
</div>
<br clear="all" />
