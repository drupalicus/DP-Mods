<div class="leftwide">
	<h3><?php print $data['title']; ?></h3>
  <p><?php print $data['field_contract_teaser'][0]['value']; ?></p>
</div>
<div class="inlinestub">
<?php if($data['field_contract_number'][0]['value']) { ?>
  <h5>Contract:</h5>
  <p><?php print $data['field_contract_number'][0]['value']; ?></p>
<?php } ?>
<?php if($data['field_contract_contact_info'][0]['value']) { ?>
	<h5>Contact Information:</h5>
  <?php print $data['field_contract_contact_info'][0]['value']; ?><br>
  <?php
    if (!empty($data['field_contract_acronym'][0]['value']))
      $title = $data['field_contract_acronym'][0]['value'];
    else
      $title = $data['title'];
  ?>
	<a href="/<?php print $data['path']; ?>"><?php print $title; ?></a>
</p>
<?php } ?>
</div>

<br clear="all">
<hr>
