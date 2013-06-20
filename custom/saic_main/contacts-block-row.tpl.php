<tr class="link">
	<td><?php print $content['title']; ?></td>
    <td>
      <?php if(!empty($content['field_ontract_secondary_info_value'])) { ?>
      <?php if($content['field_contract_secondary_link_value'] ==  'form') { ?>
          <a class="form" href="<?php print $content['field_contact_primary_info_value']; ?>">Contact Us</a>
        <?php } else { ?>
        <span class="phone">
          <?php print $content['field_ontract_secondary_info_value']; ?>
        </span>
      <?php }} ?>
  </td>
	<td>
    <?php if($content['field_contract_prim_link_value'] ==  'form') { ?>
      <a class="form" href="<?php print $content['field_contact_primary_info_value']; ?>">Contact Us</a>
    <?php } else { ?>
      <a class="info" href="<?php print $content['field_contact_primary_info_value']; ?>">Learn More</a>
    <?php } ?> 
   </td>
</tr>

