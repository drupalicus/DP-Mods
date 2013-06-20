<!-- Start: Filter Details -->
<div class="filter-details">
	<div class="filter-back"><?php print $back; ?></div>
	<div class="filter-type"><h3><?php print $type; ?></h3></div>
	<div class="filter-term"><h1 class="filter-term-title">
    <?php print $term;?><?php 
      if(!empty($count)){
        print '<span class="filter-term-count">(' . $count . ')</span>';
      } else{
	  	print '<span class="filter-term-count">(0)</span>';
	  }
    ?>
    </h1>
  </div>
</div>
<!-- End: Filter Details -->
