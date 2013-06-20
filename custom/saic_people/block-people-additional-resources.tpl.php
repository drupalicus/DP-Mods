<?php if ($node->field_person_pdf_biography[0]['filepath'] != '' || $node->field_hi_res_portrait[0]['url'] != ''): ?>
  <div class="box">
     <h3>Additional Resources</h3>
     <p>A high resolution portrait and printable biography are available by clicking on the links below.</p>
    <ul>
    <?php if ($node->field_person_pdf_biography[0]['filepath']): ?>
	    <li><a title="This link opens a new window to a PDF Biography (324k)" target="_blank" class="pdf" href="/<?php print $node->field_person_pdf_biography[0]['filepath']; ?>">PDF Biography</a></li>
    <?php endif ?>
    <?php if ($node->field_hi_res_portrait[0]['url']): ?>
	    <li><a href="<?php print $node->field_hi_res_portrait[0]['url']; ?>">Download Hi-res Portrait</a></li>
    <?php endif ?>
    </ul>
  </div>
<?php endif ?>
