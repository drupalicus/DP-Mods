<h1>Complete Products List</h1>
<div class="column">
  <ul class="product_nav">
  <?php foreach ($keys as $key) { ?>
    <li><div><?php if (in_array($key, $used)): ?><a href="#<?php if($key != '#') print strtolower($key); else print 'number'; ?>"><?php print $key; ?></a><?php else: ?><?php print $key;?><?php endif; ?></div><?php if ($key != 'Z') print '|'; ?></li>
  <?php } ?>
  </ul>
  <br clear="all">
  <?php print $content; ?>
</div>

