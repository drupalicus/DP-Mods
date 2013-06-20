<dl class="dlproducts">	
  <?php foreach ($data as $index => $product) { ?>
    <dt class="dlproducts">
      <a href="/<?php print $product['path']; ?>"><?php print $product['title']; ?></a>
    </dt>
    <dd class="dlproducts">
    <?php if(!empty($product['field_product_sub_title_value'])) { ?>
      (<?php print $product['field_product_sub_title_value']; ?>)
    <?php } ?>
    </dd>
  <?php } ?>
</dl>
