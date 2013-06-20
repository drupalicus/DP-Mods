<div class="view-project-filter">
 <form id="saic-project-index-filter-form" method="get" accept-charset="UTF-8">

<span class="form-item">
 <label for="edit-search-box">Search: </label>
 <input type="text" class="form-text" value="<?php print $_GET['search_box']; ?>" style="width:145px;" size="150" id="edit-search-box" name="search_box" maxlength="128">
</span>

<span id="edit-child-tid-wrapper" class="form-item">
 <label for="edit-child-tid">Year: </label>
 <select class="form-select" style="width:145px;" name="year[value][date]">
   <option value="" <?php if($_GET['year']['value']['date'] == 'all')  echo 'selected="selected"'?>>All</option>
  <?php foreach($years as $ind => $year ) { ?>
    <option value="<?php echo $year; ?>" <?php if($_GET['year']['value']['date']  == $year)  echo 'selected="selected"'?> ><?php echo $year; ?></option>
  <?php } ?>
  </select>
</span>

<input type="submit" class="form-submit" value="Go" name="op">

</form>
</div>
