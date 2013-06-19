<div id="hero">
  	<div class="slides">
      <?php foreach($slides as $index => $data) { ?>
        <a href="<?php print $data['url'] ?>"><img src="/<?php print $data['file_name'] ?>" /></a>
      <?php } ?>  
  	</div>
</div>
