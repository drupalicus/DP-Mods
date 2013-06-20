<?php if ($node->field_person_portrait[0]['filepath']): ?>
  <div style="line-height: 0px; border: 1px solid #BFBFBF; padding: 3px;"><?php print theme('imagecache', 'person_thumb', $node->field_person_portrait[0]['filepath'], $node->field_person_portrait[0]['data']['alt']); ?></div>
<?php endif ?>
