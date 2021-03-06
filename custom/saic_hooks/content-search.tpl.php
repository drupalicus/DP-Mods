<!-- Start: Navigator Search -->
<script type="text/javascript">
  document.observe("dom:loaded", function() {
  	// Set up the clearing of the search field
  	var searchFields=$$('.generic-search-bar form input');
  	searchFields.each(function(el) {
  		var defaultVal='<?php print $default_value; ?>';			   
  		el.observe('focus', function(e) {
  			if (el.value==defaultVal) {
  				el.value="";
  			}
  		});
  		
  		el.observe('blur', function(e) {
  			if (el.value=="") {
  				el.value=defaultVal;
  			}
  		});
  	});
  });
</script>

<form action="<?php print $action;?>" onsubmit="if ($('vc_navigator_search_value').value == '<?php print $default_value; ?>') { $('vc_navigator_search_value').value = ''; }">
  <input type="text" id="vc_navigator_search_value" name="search" value="<?php if ($_GET['search']) { print htmlspecialchars($_GET['search'], ENT_QUOTES); } else { print $default_value; } ?>" />
  <?php if($do_sort){ ?>	
  <input type='hidden' name='sort' id='vc_navigator_sort' value='<?php print saic_clean_arg($_GET['sort']) ?>'>
  <?php } ?>
	<button type="submit">Search</button>
</form>
