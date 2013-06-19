<h1>View All Contracts</h1>
<h2>SAIC delivers best-value services that today’s federal organizations need in order to integrate, modernize and upgrade their information systems. Use the alphabetical list below to quickly navigate through SAIC’s Major Task Order Contracts.</h2>
<div class="column">
<div class="alphanav">
  <ul class="product_nav">
  <?php foreach ($keys as $key) { ?>
    <li>

<div>
  <?php if (in_array($key, $used)): ?><a href="#<?php if($key != '#') print strtolower($key); else print 'number'; ?>"><?php print $key; ?></a><?php else: ?><?php print $key;?><?php endif; ?>
</div>
</li>
  <?php } ?>
  </ul>
</div>
  <br clear="all">
  <?php print $content; ?>
</div>

