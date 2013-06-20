<script>
function select_services(){
  location= document.viewsolutions.services.options[document.viewsolutions.services.selectedIndex].value;
}

function select_markets(){
  location= document.viewmarkets.markets.options[document.viewmarkets.markets.selectedIndex].value;
}
</script>

View Solutions by: <br>
<form name="viewsolutions">
  <select name="services" size="1" onChange="select_services()">
    <option value="#">Services</option>
    <?php foreach($services as $index => $service) { ?>
      <option value="http://<?php print  $_SERVER['HTTP_HOST']; ?>/<?php print $service['path']; ?>"><?php print $service['title']; ?></option>
    <? } ?>
  </select>
</form>

<form name="viewmarkets">
  <select name="markets" size="1" onChange="select_markets()">
    <option value="#">Markets</option>
    <?php foreach($markets as $index => $market) { ?>
      <option value="<?php print $market['path']; ?>"><?php print $market['title']; ?></option>
    <? } ?>
  </select>
</form>
