jQuery.extend(
  jQuery.expr[':'], {
    regex: function(a, i, m, r) {
      var r = new RegExp(m[3], 'i');
      return r.test(jQuery(a).text());
    }
  }
);

Drupal.content_podgroup = {};
Drupal.content_podgroup.initialized = false;
// bUsePopups - false for expand/collapse, true for modals
Drupal.content_podgroup.bUsePopups = false;
Drupal.content_podgroup.expandedRows=[];
Drupal.content_podgroup.regions = {};
Drupal.content_podgroup.list = {};
Drupal.content_podgroup.tree = {};
Drupal.content_podgroup.flattenedTree = {};
Drupal.content_podgroup.deltaMap = {};
Drupal.content_podgroup.table = '';
Drupal.content_podgroup.currentRow = '';
Drupal.content_podgroup.oldData = '';
Drupal.content_podgroup.destroy = false;
Drupal.content_podgroup.saveBeforeExit = false;
Drupal.content_podgroup.values = [];
Drupal.content_podgroup.currentTheme = '';
Drupal.content_podgroup.currentType = '';
// Tao changes some of the classes and markup so we need to make exceptions
Drupal.content_podgroup.isTao = false;
// Flag to prevent double clicks on drop of a new podgroup
Drupal.content_podgroup.dropFlag = false;
// Setup container for popup functions. These are called after podgroup modal popup opens    
Drupal.content_podgroup.popup = [];
// Adding vars for preventing hidden fields from getting lost
Drupal.content_podgroup.hiddenFields = null;
Drupal.content_podgroup.hiddenFieldsParent = null;
// Determines if the code runs in debug mode... aka extra logging
Drupal.content_podgroup.debug = false;


// Attach Drupal.behaviors.autocomplete to ahahCallback
// This is to ensure the dynamically created fields using
// ahah preserve their ahah functionality.
var ahahCallback = {};
ahahCallback.i = false;
Drupal.behaviors.ahahCallback = function() {
  $(document).ajaxComplete(function(e, xhr, settings) {
    if (!ahahCallback.i) {
      ahahCallback.i = true;
      Drupal.behaviors.autocomplete();
    }
  });
  ahahCallback.i = false;
}

Drupal.behaviors.content_podgroup_node_form_initialize = function(context) {
  var self = Drupal.content_podgroup;
/*
  self.list = {};
  self.tree = {};
  self.flattenedTree = {};
  self.table = '';
  self.currentRow = '';
  self.oldData = '';
  self.destroy = false;
  self.saveBeforeExit = false;
  self.values = [];
*/

  if (!self.initialized) {
    self.regions = Drupal.settings.content_podgroup_node_form.regions;
    self.currentTheme = Drupal.settings.content_podgroup_node_form.default_theme;
    self.contentType = Drupal.settings.content_podgroup_node_form.content_type;

    self._log('podgroup.init: Starting.');
    if (jQuery('fieldset.podgroup').length > 0) {
      if (jQuery('body').is('.tao')) {
        self.isTao = true;
      }
      if (self.isTao) {
        jQuery('#podgroup-js-table').replaceWith('<fieldset id="podgroup-js-table" class="collapsible fieldset titled"></fieldset>');
      } else {
        jQuery('#podgroup-js-table').replaceWith('<fieldset id="podgroup-js-table" class="collapsible"></fieldset>');
      }

      self.buildList();
      self.buildTreeFromList();
      self.buildFlattenedTree();
      self.hideInterface();
      self.buildTable();
      self.addTable('#podgroup-js-table');
      self.initConfigure();
      self.initDelete();
    }

    // If hash exists and is a valid object popup edit form for given element
    if(location.hash){
      var hash = location.hash.substr(1);
      if(jQuery('#id-' + hash).length > 0){
        self.clickConfigurePopup(hash);
      }
    }
    setTimeout(self.initInputMonitoring, 5000);
    self.initialized = true;

    self._log('podgroup.init: Complete.');
  }
};

Drupal.behaviors.content_podgroup_node_form_ahah = function(context) {
  var self = Drupal.content_podgroup;
  
  self.collapseAll();

  if (self.initialized && self.dropFlag) {
    var tableDrag = self.ahahInfo.tableDrag;
    var region = self.ahahInfo.region;
    var type = self.ahahInfo.type;
    var typeCSS = type.replace(/_/g, '-');

    // Since we just added a new podgroup instance, we need to update
    // all the weight drop downs to have one more value.
    var maxWeight = jQuery('tr.content-podgroup-instance').length;
    jQuery('tr.content-podgroup-instance').each(function() {
      var $firstOption = jQuery('select.content-podgroup-weight option:first', this);
      if ($firstOption.val() > maxWeight*-1) {
        $firstOption.before('<option value="-' + maxWeight + '">-' + maxWeight + '</option>');
      }
      var $lastOption = jQuery('select.content-podgroup-weight option:last', this);
      if ($lastOption.val() < maxWeight) {
        $lastOption.after('<option value="' + maxWeight + '">' + maxWeight + '</option>');
      }
    });

    // Get the new rows id so that we can pop the configure up once all the processing is complete
    var newRowID = '';
    var newRowClasses = jQuery('#' + typeCSS + '-items tbody tr:last').attr('class').split(' ');
    for (var newClassIdx in newRowClasses) {
      if (newRowClasses[newClassIdx].substring(0, 6).toLowerCase() == 'group_') {
        newRowID = 'id-' + newRowClasses[newClassIdx];
      }
    }

    // Set the new row's region drop down to the region the new row was dragged into
    jQuery('#' + typeCSS + '-items tbody tr:last .content-podgroup-region-select').val(region);

    // Set the new row's parent drop down to the parent of the location the new row was dragged into
    var indentCount = jQuery('div.indentation', tableDrag.oldRowElement).length;
    if (indentCount == 0) {
      jQuery('#' + typeCSS + '-items tbody tr:last .content-podgroup-parent-select').val('group_parent|0');
    }
    else {
      for (var prevRow = jQuery(tableDrag.oldRowElement).prev(); true; prevRow = jQuery(prevRow).prev()) {
        if (jQuery('div.indentation', prevRow).length == indentCount-1) {
          var prevRowID = jQuery(prevRow).attr('id');
          var prevRowIDAttr = prevRowID.split('-');
          var prevRowParent = prevRowIDAttr[1] + '|' + prevRowIDAttr[2];
          jQuery('#' + typeCSS + '-items tbody tr:last .content-podgroup-parent-select').val(prevRowParent);
          break;
        }
      }
    }

    // Find the desired weight of the newly created item
    var weightValue = -1;
    for (var prevRow = jQuery(tableDrag.oldRowElement).prev(); prevRow.length > 0; prevRow = jQuery(prevRow).prev()) {
      // If this is the first podgroup in the region
      if (jQuery(prevRow).is('.region')) {
        break;
      }
      else if (jQuery('div.indentation', prevRow).length < indentCount) {
        break;
      }
      else if (jQuery('div.indentation', prevRow).length == indentCount) {
        var prevRowID = jQuery(prevRow).attr('id');
        var prevRowSettings = prevRowID.replace('id-', '');
        weightValue = parseInt(jQuery('#edit-' + prevRowSettings.replace(/_/g, '-') + '--weight').val());
        break;
      }
    }

    // Update the weight on the newly added item to be one greater than its previous sibling
    jQuery('#' + typeCSS + '-items tbody tr:last .content-podgroup-weight').val(weightValue+1);

    // Update the weight of all the sibling podgroups after the newly created podgroup
    for (var nextRow = jQuery(tableDrag.oldRowElement).next(); nextRow.length > 0 && jQuery(nextRow).not('.region').length; nextRow = jQuery(nextRow).next()) {
      var nextIndentCount = jQuery('div.indentation', nextRow).length;
      if (nextIndentCount < indentCount) {
        break;
      }
      else if (nextIndentCount == indentCount) {
        var nextRowID = jQuery(nextRow).attr('id');
        var nextRowSettings = nextRowID.replace('id-', '');
        nextWeightValue = parseInt(jQuery('#edit-' + nextRowSettings.replace(/_/g, '-') + '--weight').val());
        jQuery('#edit-' + nextRowSettings.replace(/_/g, '-') + '--weight').val(nextWeightValue+1);
      }
    }

    // Run all the scripts to rebuild the page
    self.resetTables();

    if (jQuery('.wysiwyg-toggle-wrapper', jQuery('#' + typeCSS + '-items')).length > 0) {
      // If there is a WYSIWYG in the podgroup we need to wait for it to initialize before popping it up
      self.podgroupToShow = jQuery('#' + newRowID + ' a.podgroup-configure');
      self.podgroupShowConditional = jQuery('.wysiwyg-toggle-wrapper', jQuery('#' + typeCSS + '-items')).siblings('label').attr('for');
      self._checkIfReadyToShow();
    }
    else {
      // Pop up the configure dialog for the new podgroup row
      jQuery('#' + newRowID + ' a.podgroup-configure').click();

      // Allow Drupal behaviors to attach to form elements. This is necessary for WYSIWYG to work.
      Drupal.attachBehaviors(jQuery('#' + newRowID));
	  
      // Clear drop lock now that we have returned from the ajax
      self.dropFlag = false;
    }
  }
  self.reexpandAll();
}

// Group all function calls together that reset the table
Drupal.content_podgroup.resetTables = function() {
  var self = Drupal.content_podgroup;

  self.clearAllData();
  self.buildList();
  self.buildTreeFromList();
  self.buildFlattenedTree();
  self.updateHiddenPodgroups();
  self.buildTable();
  self.addTable('#podgroup-js-table');
  self.initConfigure();
  self.initDelete();
  self.dropFlag = false;
};

Drupal.content_podgroup.collapseAll = function() {
  var self = Drupal.content_podgroup;
  
  self.expandedRows=[];
  // For all of the edit forms
  jQuery('table.podgroup-configure-table .edit_form').each(function(index, el) {
    var $_el=jQuery(el);
	// If it has children (is expanded)
	if ($_el.children().length>0) {
	  // Add the row's id to the expanded rows list
      self.expandedRows.push($_el.parents('tr.draggable').attr('id'));
	  // Hit the collapse button for the row
	  $_el.parents('tr.draggable').find('.podgroup-collapse').click();
	}
  });
}

Drupal.content_podgroup.reexpandAll = function() {
  var self = Drupal.content_podgroup;
  
  // Go through all of the rows that are supposed to be expanded
  for (var reexpandCount=0; reexpandCount<self.expandedRows.length; reexpandCount++) {
	  // Click their configure buttons to reopen them
	  jQuery('#'+self.expandedRows[reexpandCount]).find('.podgroup-configure').click();
  }
}

Drupal.content_podgroup.onDropHandler = function() {
  var self = Drupal.content_podgroup;

  //Check if ajax lock is still on this drop area
  if (self.dropFlag) {
    return;
  }
  
  self.collapseAll();
  

  self._log('onDropHandler: Starting.');
  var tableDrag = this;

  // Unbind our mouse movements
  jQuery('#'+tableDrag.table.id).unbind('mousemove');
  // Remove our row colors
  jQuery(tableDrag.rowObject.element).css('background-color', '');

  // Remove the placeholder row if there is one
  jQuery(tableDrag.table).find('.region-empty').remove();

  if (jQuery.inArray('add', jQuery(tableDrag.oldRowElement).attr('class').split(' ')) >= 0) {
    var optionValue = jQuery('select.podgroup-options', tableDrag.oldRowElement).val();
    if (optionValue == '') {
      // The user tried to place the podgroup without selecting the type first.  Since we
      // can't validate it was dropped at an allowed place, we reset it to the bottom.
      alert("Please select a pod type before dragging the new row into your desired location.");
      self.resetTables()
    }
    else if (!tableDrag.isValidSwap()) {
      self.showStatusMessage('This podgroup may not be added there.', 'warning', tableDrag.table.id);
      self._log('onDropHandler: Not valid swap. Rebuilding table.');
      self.resetTables();
    }
    else {
	  // Ensure everything is closed.
	  self.collapseAll();
		
      // Invoke a new instance of the podgroup
      var region = optionValue.split('|')[0];
      var type = optionValue.split('|')[1];

      // Add drop flag to the drop area
      self.dropFlag = true;
      self.ahahInfo = {tableDrag: tableDrag, region: region, type: type};
      jQuery('#edit-' + type.replace(/_/g, '-') + '-' + type.replace(/_/g, '-') + '-add-more').trigger('mousedown');
    }
  }
  else {
    if (!tableDrag.isValidSwap()) {
      self.showStatusMessage('This podgroup may not be added there.', 'warning', tableDrag.table.id);
      self._log('onDropHandler: Not valid swap. Rebuilding table from podgroups.');
      self.resetTables();
    }
    else {
      var $table = jQuery(tableDrag.table);
      self.rescanTable($table);
      self.buildTreeFromList();
      self.buildFlattenedTree();
      self.updateHiddenPodgroups();
    }
  }
  
  self.reexpandAll();
};
    
Drupal.content_podgroup.showStatusMessage = function(msg, type, table) {
  alert(msg);
};

Drupal.content_podgroup.updateHiddenPodgroups = function() {
  var self = Drupal.content_podgroup;

  for (var region in self.flattenedTree[self.currentTheme]) {
    for (var itemIdx in self.flattenedTree[self.currentTheme][region]) {
      var item = self.flattenedTree[self.currentTheme][region][itemIdx];
      var itemKey = item['type'].replace(/_/g, '-') + '-' + item['delta'];
      jQuery('#edit-' + itemKey + '--weight').val(item['weight']);
      jQuery('#edit-' + itemKey + '--region').val(region);

      var parentOptionIdx = self.deltaMap[item.parent_type + '-' + item.parent_delta];
      if (parentOptionIdx != undefined) {
        var parentOption = self.flattenedTree[self.currentTheme][region][parentOptionIdx];
        var parentOptionValue = parentOption['type'] + '|' + parentOption['delta'];
  //      if (parentOption['type'] == nestingType && !(nestingType == item['type'] && parentOption['delta'] == item['delta'])) {
        if (parentOption['delta'] != item['delta']) {
          var existingParentOption = jQuery('#edit-' + itemKey + '--parent option[value=' + parentOptionValue + ']');
          if (existingParentOption.length > 0) {
            existingParentOption.html(parentOption['title']);
          }
          else {
            var newParentOption = '<option value="' + parentOptionValue + '">' + parentOption['title'] + '</option>';
            jQuery('#edit-' + itemKey + '--parent option:last').after(newParentOption);
          }
        }
      }

      jQuery('#edit-' + itemKey + '--parent').val(item['parent_type'] + '|' + item['parent_delta']);
    }
  }
};

Drupal.content_podgroup.rescanTable = function($table) {
  var self = Drupal.content_podgroup;

  var tempList = {};
  var regionId = $table.attr('id').substr(22);
  jQuery.each(self.list[self.currentTheme][regionId], function(i){
    tempList['id-' + this.type + '-' + this.delta] = this;
  });

  self.clearRegionData(regionId);
  var x = 0;
  var parentList = [];
  var previousItem = ['id-group_parent-0', -1];
  var weightCounterStack = [];
  var weight = 0;

  var rows = jQuery('tr.draggable', $table);
  for (var i = 0; i < rows.length; i++) {
    var $row = rows[i];
    var id = jQuery($row).attr('id');

    // Check to ensure it has an ID, if it doesn't have an ID it isn't a podgroup instance so we should ignore it.
    if (id != '') {
      var curIndentCount = jQuery('div.indentation', $row).length;

      if (curIndentCount > previousItem[1]) {
        parentList.push(previousItem);
        weightCounterStack.push(weight);
        weight = 0;
      }
      else if (curIndentCount <= parentList[parentList.length-1][1]) {
        for (var parentIndentCount = parentList.pop()[1], weight = weightCounterStack.pop(); curIndentCount <= parentList[parentList.length-1][1]; parentIndentCount = parentList.pop()[1], weight = weightCounterStack.pop());
      }

      tempList[id].weight = weight;
      tempList[id].delta = id.split('-')[2];

      tempList[id].parent_type = parentList[parentList.length-1][0].split('-')[1];
      tempList[id].parent_delta = parentList[parentList.length-1][0].split('-')[2];
      tempList[id].depth = curIndentCount;

      self.list[self.currentTheme][regionId][x] = tempList[id];
      previousItem = [id, curIndentCount];

      weight++;
      x++;
    }
  }
};

Drupal.content_podgroup.isValidSwap = function() {
  var self = Drupal.content_podgroup;

  var tableDrag = this;
  var row = tableDrag.oldRowElement;
  var rowObject = tableDrag.rowObject;
  self._log('podgroup.isValidSwap: Starting.');
  if (rowObject.indentEnabled) {
    var prevRow, nextRow;
    if (rowObject.direction == 'down') {
      prevRow = row;
      nextRow = jQuery(row).next('tr').get(0);
    }
    else {
      prevRow = jQuery(row).prev('tr').get(0);
      nextRow = row;
    }
    rowObject.interval = rowObject.validIndentInterval(prevRow, nextRow);

    // We have an invalid swap if the valid indentations interval is empty.
    if (rowObject.interval.min > rowObject.interval.max) {
      return false;
    }
  }

  // Do not let an un-draggable first row have anything put before it.
  if (rowObject.table.tBodies[0].rows[0] == row && $(row).is(':not(.draggable)')) {
    return false;
  }

  // Now that we are sure it is in a valid drop area, let's see if it is
  // allowed to be in this area by pod type.      
  var $element = jQuery(row);
  var region = rowObject.table.id.substr(22);
  var type, prev_type;
      
  // Find our type, if the id is null it means it's a new element being added.
  if ($element.attr('id') == '') {
    var optionValue = jQuery('select.podgroup-options', tableDrag.oldRowElement).val();
    type = optionValue.split('|')[1];
  } 
  else {
    type = $element.attr('id').split('-')[1];
  }
      
  // Find our parent and if it is null means we are at the root (ie. group_parent).
  var parent = self._findParentRow(row);
  if (parent == null) {
    var prev_type = 'group_parent';
  }
  else if(parent === undefined){
    var prev_type = 'error';
  }
  else {
    var prev_type = jQuery(parent).attr('id').split('-')[1];  
  }

  // We do !! to make sure these are defined.  It's a cheap trick to not
  // use undefined variables.  The real logic is making sure nesting is
  // equal to 1 for the region/type we are trying to drop into.
  if (!!prev_type && !!type && !!region && 
    !self.regions[self.currentTheme][region].options[type].nesting[prev_type]
    || prev_type == 'error') {
    return false;
  }

  // Make sure we aren't dragging the row back underneath the Add row
  var addRowIndex = jQuery('#' + tableDrag.table.id).find('.region-add').attr('rowIndex');     
  if (rowObject.element.rowIndex >= addRowIndex) {
    return false;
  }

  return true;
};
    
Drupal.content_podgroup.onDragHandler = function() {
  var self = Drupal.content_podgroup;

  if (self.dropFlag) {
    return;
  }

  var tableDrag = this;
  self._log('podgroup.onDragHandler: Starting.');
  
  jQuery('#'+tableDrag.table.id).mousemove(function() {
    var region = tableDrag.table.id.substr(22);

    // Getting type we need to check to see if it's a new element or not.
    if (jQuery(tableDrag.rowObject.element).attr('id') == '') {
      var optionValue = jQuery('select.podgroup-options', tableDrag.rowObject.element).val();
      var type = optionValue.split('|')[1];
    }
    else {
      var type = jQuery(tableDrag.rowObject.element).attr('id').split('-')[1];  
    }
        
    // Find our parent and if it is null means we are at the root (ie. no parent).
    var parent = self._findParentRow(tableDrag.rowObject.element);

    // null is the top level
    if (parent === null) {
      var drop_type = 'group_parent';
    }
    // Undefined is a bad position (ie indented at the top)
    else if(parent === undefined) {
      var drop_type = 'error';
    }
    else {
      var drop_type = jQuery(parent).attr('id').split('-')[1];  
    }

    var addRowIndex = jQuery('#' + tableDrag.table.id).find('.region-add').attr('rowIndex');  
    if ((!!region && !!type && !!drop_type &&
        !self.regions[self.currentTheme][region].options[type].nesting[drop_type]) ||
        tableDrag.rowObject.element.rowIndex >= addRowIndex ||
        drop_type === 'error') {
      // If in an illegal place make the row red
      jQuery(tableDrag.rowObject.element).css('background-color', '#ff9999');
    }
    else {
      // If in a legal place make the row green
      jQuery(tableDrag.rowObject.element).css('background-color', '#99ff99');
    }

    // If the next element is the Add row, hide the dropzone row
    if (jQuery(tableDrag.rowObject.element).next().is('tr.region-add')) {
      jQuery('#' + tableDrag.table.id).find('.region-empty').hide();
    }
    else {
      jQuery('#' + tableDrag.table.id).find('.region-empty').show();
    }
  });
};
    
Drupal.content_podgroup._findParentRow = function(row) {
  var $row = jQuery(row);
  var indentation = jQuery('div.indentation', $row).length;
  var parent = null;
  while ($row.length > 0) {
    $prev = $row.prev('tr.draggable');
    if (jQuery('div.indentation', $prev).length < indentation) {
      parent = $prev.get(0);
      break;
    }
    $row = $prev;
  }
  return parent;
};

Drupal.content_podgroup.getListItem = function(region, type, delta) {
  var self = Drupal.content_podgroup;
  self._log('Region: ' + region + ' Type: ' + type + ' Delta: ' + delta);
};

Drupal.content_podgroup.clearAllData = function() {
  var self = Drupal.content_podgroup;

  self.list = {};
  self.tree = {};
  self.flattenedTree = {};
  self.deltaMap = {};
  self.table = '';
};

Drupal.content_podgroup.clearRegionData = function(regionId) {
  var self = Drupal.content_podgroup;

  self.list[self.currentTheme][regionId] = [];
  self.tree[self.currentTheme][regionId] = [];
  self.flattenedTree[self.currentTheme][regionId] = [];
  self.table = '';
};

Drupal.content_podgroup.buildTable = function() {
  var self = Drupal.content_podgroup;

  self._log('podgroup.buildTable: Starting.');
  for (var region in self.regions[self.currentTheme]) {
    self.table += '<fieldset class="collapsible"><legend>' + self.regions[self.currentTheme][region]['label'] + '</legend>';
    self.table += '<table class="podgroup-configure-table sticky-enabled" id="podgroup-region-table-' + region + '">'
    self.table += '<tbody>';

    var zebra = 'odd';
    if (self && self.flattenedTree 
      && self.flattenedTree[self.currentTheme]
      && self.flattenedTree[self.currentTheme][region]) {
      for (delta in self.flattenedTree[self.currentTheme][region]) {
        var element = self.flattenedTree[self.currentTheme][region][delta];
        var depth = self.flattenedTree[self.currentTheme][region][delta].depth;
        zebra = (delta % 2 == 0) ? 'odd' : 'even';
        self.table += self._drawRow(element, zebra, depth);
      }
    }
    else {
      self.table += self._getEmptyRow();
    }

    self.table += self._drawRowOptions(region, self.regions[self.currentTheme][region]['options_by_category'], zebra);
    self.table += '</tbody>';
    self.table += '</table>';
    self.table += '</fieldset>';
  }
  self._log('podgroup.buildTable: Complete.');
};

Drupal.content_podgroup._getEmptyRow = function() {
  return '<tr class="region-empty odd"><td colspan="3"><em>No podgroups in this region</em></td></tr>';
};

Drupal.content_podgroup._buildTableFromTree = function(list, zebra, depth) {
  var self = Drupal.content_podgroup;

  zebra = (zebra == 'even') ? 'odd' : 'even';
  var output = '';
  for (i in list) {
    output += self._drawRow(list[i], zebra, depth);
    if (list[i].children.length > 0) {
      zebra = (zebra == 'even') ? 'odd' : 'even';
      return self._buildTableFromTree(list[i].children, zebra, depth+1);
    }
  }

  return output;
};
    
Drupal.content_podgroup._drawRow = function(element, zebra, depth) {
  var self = Drupal.content_podgroup;

  // Test for error in element or one of the podgroups children elements
  var error_class = '';
  var $err = jQuery('.' + element.type + '-' + element.delta + '.error');
  if ($err.length) {
    error_class = ' error ';
  }
  else {
    var $err = jQuery('.' + element.type + '-' + element.delta).find('.error');
    if ($err.length) {
      error_class = ' error ';
    }
  }

  var output = '';
  self._log("Drawing Element: ");
  self._log(element);
  output += '<tr class="draggable ' + zebra + (element.removed ? ' content-multiple-removed-row' : '') + error_class + '" id="id-' + element.type + '-' + element.delta + '">';
  output += '<td>';
  for (i = 0; i < depth; i++) {
    output += '<div class="indentation"></div>';
  }
  output +=  '<span class="title">' + element.title + ' (' + element.type_label.replace(/(<.*?>)/ig,"") + ')</span></td>';
  output += '<td>';
  output += '<select class="sort"><option value="1">1</option><option>2</option></select>';
  output += '<input class="pgpid" value="' + element.parent_type + '|' + element.parent_delta + '"/>';
  output += '<input class="pgmid" value="' + element.type + '|' + element.delta + '"/>';
  output += '</td>';
  output += '<td class="podgroup-configure-column">';
  output += '<a class="podgroup-configure" href="#"><span class="before">+</span> Configure <span class="after">+</span></a>';
  output += '<a class="podgroup-collapse" style="display: none;" href="#"><span class="before">-</span> Configure <span class="after">-</span></a>';
  if (element.removed) {
    output += ' <a title="' + Drupal.t('Remove this item') + '" class="content-multiple-remove-button" href="javascript:void(0)"></a>';
  }
  else {
    output += ' <a title="' + Drupal.t('Restore this item') + '" class="content-multiple-remove-button" href="javascript:void(0)"></a>';
  }
  output += '</td>';
  output += '</tr>';

  return output;
};

Drupal.content_podgroup._drawRowOptions = function(region, options, zebra) {
  var self = Drupal.content_podgroup;

  self._log("Drawing options");
  self._log(options);
  var output = '';

  zebra = (zebra == 'even') ? 'odd' : 'even';
  output += '<tr class="region region-add ' + zebra + '">';
  output += '<td class="region" colspan="3">Add</td>';
  output += '</tr>';

  zebra = (zebra == 'even') ? 'odd' : 'even';
  output += '<tr class="draggable add ' + zebra + '">';
  output += '<td>';
  output += '<select class="podgroup-options">';
  output += '<option value="">Add a pod</option>';
  for (var category in options) {
    output += '<optgroup label="' + category + '">';
    for (var i in options[category]) {
      output += '<option value="' + region + '|' + i + '">' + options[category][i]['label'] + '</option>';
    }
    output += '</optgroup>';
  }
  output += '</select>';
  output += '</td>';
  output += '<td>';
  output += '<select class="sort"><option value="1">1</option><option>2</option></select>';
  output += '<input class="pgpid" value=""/>';
  output += '<input class="pgmid" value=""/>';
  output += '</td>';
  output += '<td class="podgroup-configure-column"></td>';
  output += '</tr>';

  return output;
};

Drupal.content_podgroup.addTable = function(domLocation) {
  var self = Drupal.content_podgroup;

  if (self.isTao) {
    jQuery(domLocation).html('<legend><span class="fieldset-title"><span class="icon"></span><a class="active" href="#fieldset">Podgroups</a></span></legend><div class="fieldset-content" style="display: block;">' + self.table + '</div>');
  }
  else {
    jQuery(domLocation).html('<legend>Podgroups</legend>' + self.table);
  }

  $('table.podgroup-configure-table').filter(':not(.tabledrag-processed)').each(function() {
    var $table = jQuery(this);
    var base = $table.attr('id');
    var tableSettings = Drupal.settings.tableDrag[base];
    Drupal.tableDrag[base] = new Drupal.tableDrag(this, tableSettings);
    jQuery('#' + base).addClass('tabledrag-processed');

    // Override the handlers for tabledrag.
    Drupal.tableDrag[base].onDrag = self.onDragHandler;
    Drupal.tableDrag[base].onDrop = self.onDropHandler;
    Drupal.tableDrag[base].isValidSwap = self.isValidSwap;
  });
};

Drupal.content_podgroup.hideInterface = function() {
  jQuery('fieldset.podgroup').parent().hide();
};

Drupal.content_podgroup.initConfigure = function() {
  var self = Drupal.content_podgroup;

  jQuery('a.podgroup-configure').click(self.clickConfigure);
  jQuery('a.podgroup-collapse').click(self.clickCollapse);
};

Drupal.content_podgroup.clickConfigure = function(e) {
  var self = Drupal.content_podgroup;

  var clickedRow = jQuery(this).parent().parent();
  var id = clickedRow.attr('id').substr(3);

  
  self.clickConfigurePopup(id);
  
  return false;
};

Drupal.content_podgroup.clickConfigurePopup = function(id) {
  var self = Drupal.content_podgroup;

  var clickedRow = jQuery('#id-' + id);
  var configureRow = jQuery('tr.'+id);
  var dataCell = configureRow.children('td').eq(1);
  var title = jQuery('td:first span.title', clickedRow).html();

  self.currentRow = configureRow;
  self._log(dataCell);
  
  if (Drupal.content_podgroup.bUsePopups) {
    self.createModal(dataCell, id, title);
  } else {
    self.copyInContents(dataCell, id, title);
  }

  // Allow for functions to be executed after the popup
  for(var func in Drupal.content_podgroup.popup) {
    Drupal.content_podgroup.popup[func](id);
  }
};

Drupal.content_podgroup.clickCollapse = function(e) {
  var self = Drupal.content_podgroup;

  var clickedRow = jQuery(this).parent().parent();
  var id = clickedRow.attr('id').substr(3);

  self.clickCollapsePopup(id);
  
  return false;
};

Drupal.content_podgroup.clickCollapsePopup = function(id) {
  var self = Drupal.content_podgroup;

  var clickedRow = jQuery('#id-' + id);
  var configureRow = jQuery('tr.'+id);
  var dataCell = configureRow.children('td').eq(1);
  var title = jQuery('td:first span.title', clickedRow).html();

  self.currentRow = configureRow;
  self._log(dataCell);
  
  if (Drupal.content_podgroup.bUsePopups) {
    // Do nothing as this shouldn't ever be called with popups
  } else {
    self.copyOutContents(dataCell, id, title);
  }
};
        
Drupal.content_podgroup.initDelete = function() {
  var self = Drupal.content_podgroup;

  jQuery('a.content-multiple-remove-button')
    .unbind('click')
    .click(self.clickDelete);

  jQuery('tr.content-multiple-removed-row a.content-multiple-remove-button')
    .unbind('click')
    .click(self.undoItem);
};

Drupal.content_podgroup.clickDelete = function() {
  var self = Drupal.content_podgroup;

  var clickedRow = jQuery(this).parent().parent();
  var id = clickedRow.attr('id').substr(3);
  self.confirmDeleteModal(id);
};

Drupal.content_podgroup.confirmDeleteModal = function(id) {
  var self = Drupal.content_podgroup;

  var $dialog = jQuery('<div id="pg-delete-dialog"></div>');
  $dialog.dialog({
    title: Drupal.t('Remove Podgroup'),
    modal: true,
    width: '500px',
    buttons: {
      Yes: function() {
        self.deleteItem(id);
        self.initDelete();
        jQuery(this).dialog('close');
      },
      No: function() {
        jQuery(this).dialog('close');
      }
    },
    close: function(event, ui) {
      jQuery(this).dialog('destroy');
      jQuery('#pg-delete-dialog').remove();
    }
  });

  $dialog.append('<div class="delete-confirm">' +
    Drupal.t('Are you sure you want to delete this item?') +
    '<br/><em>' + Drupal.t('All children items will be removed as well.') + '</em>' + '</div>');

  $dialog.dialog('open');
};

Drupal.content_podgroup.deleteItem = function(id) {
  var $row = jQuery('#id-' + id);
  var indentation = jQuery('div.indentation', $row).length;

  // Mark parent for deletion
  jQuery('input#edit-' + id.replace(/_/g, '-') + '--remove').attr('checked', true);
  $row.addClass('content-multiple-removed-row');
  jQuery('.content-multiple-remove-button', $row).attr('title', Drupal.t('Restore this item'));

  // Find children and mark for deletion as well.
  $next = $row.next('tr.draggable');
  while ($next.length > 0) {
    if (jQuery('div.indentation', $next).length > indentation) {
      var child = $next.attr('id').substr(3);
      jQuery('input#edit-' + child.replace(/_/g, '-') + '--remove').attr('checked', true);
      $next.addClass('content-multiple-removed-row');
      jQuery('.content-multiple-remove-button', $next).attr('title', Drupal.t('Restore this item'));
    }
    else if (jQuery('div.indentation', $next).length <= indentation) {
      break;
    }
    $next = $next.next('tr.draggable');
  }
};

Drupal.content_podgroup.undoItem = function() {
  var self = Drupal.content_podgroup;

  var $row = jQuery(this).parent().parent();
  var id = $row.attr('id').substr(3);
  jQuery('input#edit-' + id.replace(/_/g, '-') + '--remove').attr('checked', false);
  $row.removeClass('content-multiple-removed-row');
  jQuery('.content-multiple-remove-button', $row).attr('title', Drupal.t('Remove this item'));
  self.initDelete();
};

Drupal.content_podgroup.copyInContents = function($cell, id, title) {
  var _self = Drupal.content_podgroup;
  
  var $_tr=jQuery('#id-'+id);
  
  // Ensure a div.edit_form exists
  var $_form=$_tr.find('td:first div.edit_form');
  if ($_form.length==0) {
	 $_tr.find('td:first').append('<div class="edit_form"></div>');
  }
  $_form=$_tr.find('td:first div.edit_form');
  
  // The form hasn't been previously cleared out and therefore shouldn't be emptied now.
  if ($_form.children().length!=0) {
	  return;
  }
  
  // Clear the form
  $_form.empty();
  
  // Copy the contents in
  $cell.children().each(function(index, el) {
    $_form.append(jQuery(el));
  });
  
  // Hide the configure button
  $_tr.find('.podgroup-configure').hide();
  
  // Show the collapse button
  $_tr.find('.podgroup-collapse').show();
}

Drupal.content_podgroup.copyOutContents = function($cell, id, title) {
  var _self = Drupal.content_podgroup;
  
  var $_tr=jQuery('#id-'+id);
  
  var $_form=$_tr.find('td:first div.edit_form');
  
  // Set the new title
  var newTitle = jQuery('#edit-' + id.replace(/_/g, '-') + '--title', $_form).val();
  var typeLabel = jQuery('fieldset.' + id.split('-')[0].replace(/_/g, '-') + ' legend:first').html();
  typeLabel = typeLabel.replace(/(<.*?>)/ig,"");
  jQuery('#id-' + id + ' td:first span.title').html(newTitle + ' (' + typeLabel + ')');
	
  // $_tr.find('.title').html($_form.find('input:first').val());
  
  // Copy the contents back out
  $_form.children().each(function(index, el) {
    $cell.append(jQuery(el));
  });
  
  // Show the configure button
  $_tr.find('.podgroup-configure').show();
  
  // Hide the collapse button
  $_tr.find('.podgroup-collapse').hide();
}

Drupal.content_podgroup.createModal = function($cell, id, title) {
  var _self = Drupal.content_podgroup;

  // Get form for later use
  var form = $cell.parents('form');

  // Store the old values
  _self._storeValues($cell);

  // Create a dialog element
  var $dialog = jQuery('<div id="pg-dialog"></div>');

  // Set it up as a dialog
  $dialog.dialog({
    title: title,
    modal: true,
    width: '50%',
    buttons: {
	  Cancel: function() {
		var bMayExit=true;
		
	    if (_self._canRestoreValues($(this))===false) {
			bMayExit=window.confirm("You have changed at least one file in this form.\nDue to browser security restrictions, we will not be able to undo file changes.\nDo you still want to cancel changes to the other fields?");
		}
		
		if (bMayExit === true) {
          _self.saveBeforeExit = false;
          $(this).dialog("close");
		}
	  },
      Ok: function() {
        _self.saveBeforeExit = true;
        $(this).dialog("close");
      }
    },
    close: function(event, ui) {
      _self.destroyModal(this, id);
    }
  });

  // Display it
  $dialog.dialog('open');

  // Allow auto-complete to expand the dialog to display
  // the list of options beyond the borders of the container
  jQuery('.ui-dialog').css('overflow', 'visible');

  // Find out if the contents contains any open WYSIWYGs
  var openWYSIWYGs = [];
  $cell.find('.wysiwyg-toggle-wrapper a').each(function(index, el) {
    openWYSIWYGs[index] = false;
    if (jQuery(el).html().toString().indexOf('Disable') != -1) {
      // And, if so, store that it was open
      openWYSIWYGs[index] = true;
      // And disable it
      jQuery(el).trigger('click');
    }
  });

  // Copy the form and required form fields into the dialog
  var formString = '<form action="' + form.attr("action") + '" accept-charset="UTF-8" method="post" enctype="multipart/form-data" />';
  $dialog.append(formString);
  $dialog.children('form').append(form.find("input[name='form_build_id']"));
  $dialog.children('form').append(form.find("input[name='form_token']"));
  $dialog.children('form').append(form.find("input[name='form_id']"));

  // Copy the contents in
  $cell.children().each(function(index, el) {
    $dialog.children('form').append(jQuery(el));
  });

  // Create a reference back
  $cell.empty().html('<div id="pg-configureHTML"></div>');

  // Reopen any WYSIWYGs that we closed
  $dialog.find('.wysiwyg-toggle-wrapper a').each(function(index, el) {
    if (openWYSIWYGs[index]) {
      jQuery(el).trigger('click');
    }
  });

  // Prevent form submit from inside text field when user hits Enter
  $dialog.find('input[type=text]').keypress(function(e){
    if (e.which == 13) {
      //jQuery('.ui-dialog').find(":button:contains('Ok')").click();
      e.preventDefault();
    }
  });

  // Allow other modules to attach behaviors to execute after popup.
  // They can do this with this code:
  //    self.popup.push(function($dialog){});
  jQuery.each(_self.popup, function() {
    this($dialog);
  });
};

Drupal.content_podgroup.destroyModal = function(modal, id) {
  var self = Drupal.content_podgroup;

  // If we are saving the content 
  if (self.saveBeforeExit) {
    // Update the title on the podgroup draggable row
    var newTitle = jQuery('#edit-' + id.replace(/_/g, '-') + '--title', modal).val();
    var typeLabel = jQuery('fieldset.' + id.split('-')[0].replace(/_/g, '-') + ' legend:first').html();
    typeLabel = typeLabel.replace(/(<.*?>)/ig,"");
    jQuery('#id-' + id + ' td:first span.title').html(newTitle + ' (' + typeLabel + ')');

    // Update the title for all occurances of the pod in the Parent drop downs
    jQuery('.content-podgroup-parent-select option[value=' + id.replace(/-/g, '|') + ']').html(newTitle);

    // Update the title in the podgroup.list so when we rebuild the list the new value will be available
    var newRegion = jQuery('#edit-' + id.replace(/_/g, '-') + '--region').val();
    for (var idx in self.list[self.currentTheme][newRegion]) {
      if (self.list[self.currentTheme][newRegion][idx]['type'] == id.split('-')[0] && self.list[self.currentTheme][newRegion][idx]['delta'] == id.split('-')[1]) {
        self.list[self.currentTheme][newRegion][idx].title = newTitle;
      }
    }
  }

  // Find the cell again from the handle we left
  var $cell = jQuery('#pg-configureHTML').parent();
  // Remove the handle
  $cell.empty();

  // Find out if the contents contains any open WYSIWYGs
  var openWYSIWYGs = [];
  jQuery(modal).find('.wysiwyg-toggle-wrapper a').each(function(index, el) {
    openWYSIWYGs[index] = false;
    if (jQuery(el).html().toString().indexOf('Disable') != -1) {
      // And, if so, store that it was open
      openWYSIWYGs[index] = true;
      // And disable it
      jQuery(el).trigger('click');
    }
  });

  var form = $cell.parents('form');
  form.append(jQuery(modal).find("input[name='form_build_id']"));
  form.append(jQuery(modal).find("input[name='form_token']"));
  form.append(jQuery(modal).find("input[name='form_id']"));

  // Copy the fields back from the modal to the original location
  jQuery(modal).children('form').children().each(function(index, el) {
    $cell.append(jQuery(el));
  });

  // If we are not saving the values
  if (self.saveBeforeExit == false) {
    // Overwrite the new values with the original ones
    self._restoreValues($cell);
  }

  // Reopen any WYSIWYGs that we closed
  $cell.find('.wysiwyg-toggle-wrapper a').each(function(index, el) {
    if (openWYSIWYGs[index]) {
      jQuery(el).trigger('click');
    }
  });

  self.currentRow = '';
  self.destroy = true;
  jQuery(modal).dialog('destroy');
  jQuery('#pg-dialog').remove();

  self.saveBeforeExit = false;
};

Drupal.content_podgroup._storeValues = function($cell) {
  var self = Drupal.content_podgroup;

  jQuery('input, select, textarea', $cell).each(function(i){
    var id = jQuery(this).attr('id');
    var val = jQuery(this).val();
    self.values[id] = val;
    self._log("podgroup._storeValues: STORING <"+id+"> VALUE: "+val);
  });
};

Drupal.content_podgroup._canRestoreValues = function($parent) {
  var bCanRestore=true;
  var _self = Drupal.content_podgroup;
  
  jQuery('input[type=file]', $parent).each(function(i){
    var id = jQuery(this).attr('id');
    var val = jQuery(this).val();
	if (_self.values[id].toString()!=val.toString()) {
		bCanRestore=false;
	}
  });
  return bCanRestore;
};

Drupal.content_podgroup._restoreValues = function($cell) {
  var self = Drupal.content_podgroup;

  jQuery('input, select, textarea', $cell).each(function(i){
    var id = jQuery(this).attr('id');
    var val = jQuery(this).val();
    if (!jQuery(this).is('input[type=file]')) {
      // For everything other than file inputs which can't be rewritten anyway
      jQuery(this).val(self.values[id]);
      self._log("podgroup._restoreValues: RESTORING <" + id + "> VALUE: " + self.values[id]);
    }
    else {
      // File inputs
      self._log("podgroup._restoreValues: SKIPPING file input <" + id + "> VALUE: " + self.values[id]);
	}
  });
};

Drupal.content_podgroup.buildList = function() {
  var self = Drupal.content_podgroup;

  self._log('podgroup.buildList: Starting');

  var podgroupTypes = {};
  for (var theme in self.regions) {
    for (var region in self.regions[theme]) {
      for (var groupType in self.regions[theme][region]['options']) {
        podgroupTypes[groupType] = true;
      }
    }
  }

  for(var podgroupType in podgroupTypes) {
    jQuery('fieldset.' + podgroupType.replace(/_/g, '-')).each(function(i) {
      var type_label = jQuery('legend:first', this).html();

      jQuery('table.content-podgroup-table tbody tr.content-podgroup-instance', this).each(function(j) {
        var element = jQuery(this);
        var region = jQuery('td.content-podgroup-region-cell select option:selected', element).val();
        var theme = self.currentTheme;
        var title = jQuery.trim(jQuery('input.content-podgroup-title', this).val());
        var parent_type = jQuery('td.content-podgroup-parent-cell select option:selected', this).val();
        if (parent_type) {
          parent_type = parent_type.split('|')[0];
        }
        var parent_delta = jQuery('td.content-podgroup-parent-cell select option:selected', this).val();
        if (parent_delta) {
          parent_delta = parent_delta.split('|')[1];
        }
        var weight = parseInt(jQuery('td.content-podgroup-weight-cell select option:selected', this).val());
        var delta = j;
        var classes = element.attr('class').split(' ');
        for (var i in classes) {
          var classParts = classes[i].split('-');
          if (classParts[0] == podgroupType && classParts[1] && !isNaN(classParts[1])) {
            delta = classParts[1];
            break;
          }
        }

        var removed = (jQuery('td.content-podgroup-remove-cell input:checked', this).length > 0);

        if (!self.list[theme]) {
          self.list[theme] = {};
        }
        if (!self.list[theme][region]) {
          self.list[theme][region] = [];
        }

        self.list[theme][region][self.list[theme][region].length] = {
          title: title,
          parent_type: parent_type,
          parent_delta: parent_delta,
          type_label: type_label,
          type: podgroupType,
          weight: weight,
          delta: delta,
          removed: removed,
          region: region,
          theme: theme,
          children: [],
          depth: -1
        };
      });
    });
  }

  self._log('podgroup.buildList: Completed');
};
    
Drupal.content_podgroup._buildTreeFromListRecursion = function(podgroups, parent_delta) {
  var self = Drupal.content_podgroup;

  for (var i in podgroups) {
    if (podgroups[i]['type'] == podgroups[parent_delta]['type'] && podgroups[i]['delta'] == podgroups[parent_delta]['delta']) {
      continue;
    }

    if (podgroups[i]['parent_type'] == podgroups[parent_delta]['type']
      && podgroups[i]['parent_delta'] == podgroups[parent_delta]['delta']) {
      self._buildTreeFromListRecursion(podgroups, i);

      if (!podgroups[parent_delta]['children']) {
        podgroups[parent_delta]['children'] = {};
      }

      var num_of_children = podgroups[parent_delta]['children'].length;
      for (var insert_index = 0; insert_index < num_of_children; insert_index++) {
        if (podgroups[parent_delta]['children'][insert_index]['weight'] > podgroups[i]['weight']) {
          break;
        }
      }

      var first_half = podgroups[parent_delta]['children'].slice(0, insert_index);
      if (insert_index < podgroups[parent_delta]['children'].length) {
        second_half = podgroups[parent_delta]['children'].slice(insert_index);
      }
      else {
        second_half = [];
      }

      podgroups[parent_delta]['children'] = self._array_merge(first_half, [podgroups[i]], second_half);

      delete podgroups[i];
    }
  }

  return podgroups;
};

Drupal.content_podgroup.buildTreeFromList = function() {
  var self = Drupal.content_podgroup;

  self._log('podgroup.buildTreeFromList: Starting');
  self.tree[self.currentTheme] = {};
  var tempList = self._copyObject(self.list);
  for (var region in tempList[self.currentTheme]) {
    var podgroups = tempList[self.currentTheme][region];
    for (var i in podgroups) {
      if (podgroups[i]['parent_type'] == 'group_parent' && podgroups[i]['parent_delta'] == 0) {
        podgroups = self._buildTreeFromListRecursion(podgroups, i);
      }
    }

    if (!self.tree[self.currentTheme][region]) {
      self.tree[self.currentTheme][region] = [];
    }

    // Sort the parent level podgroups
    podgroups.sort(self._sort_podgroups_by_weight);

    self.tree[self.currentTheme][region] = podgroups;
  }

  self._log('podgroup.buildTreeFromList: Completed');
};

Drupal.content_podgroup._sort_podgroups_by_weight = function(a, b) {
  return a.weight - b.weight;
};

Drupal.content_podgroup.buildFlattenedTree = function() {
  var self = Drupal.content_podgroup;
  self.flattenedTreeCount = 0;

  for (var theme in self.tree) {
    for (var region in self.tree[theme]) {
      self.flattenedTree[theme] = self.flattenedTree[theme] || {};
      self.flattenedTree[theme][region] = self.flattenedTree[theme][region] || {};
      self.flattenedTree[theme][region] = self._flattenTree(self.tree[theme][region], 0);
    }
  }
};

Drupal.content_podgroup._flattenTree = function(branch, depth) {
  var self = Drupal.content_podgroup;

  var newList = {};
  for (var i in branch) {
    branch[i].depth = depth;
    newList[self.flattenedTreeCount] = branch[i];
    self.deltaMap[branch[i].type + '-' + branch[i].delta] = self.flattenedTreeCount;
    self.flattenedTreeCount++;
    if (branch[i] && branch[i]['children'].length > 0) {
      newList = jQuery.extend(newList, self._flattenTree(branch[i]['children'], depth+1));
    }
  }

  return newList;
};

Drupal.content_podgroup._array_merge = function() {
  var args = Array.prototype.slice.call(arguments), retObj = {}, k, j = 0, i = 0, retArr = true;
  for (i = 0; i < args.length; i++) {
    if (!(args[i] instanceof Array)) {
      retArr = false;
      break;
    }

    if (retArr) {
      retArr = [];
      for (i = 0; i < args.length; i++) {
        retArr = retArr.concat(args[i]);
      }
      return retArr;
    }
    var ct = 0;

    for (i = 0, ct = 0; i < args.length; i++) {
      if (args[i] instanceof Array) {
        for (j = 0; j < args[i].length; j++) {
          retObj[ct++] = args[i][j];
        }
      } 
      else {
        for (k in args[i]) {
          if (args[i].hasOwnProperty(k)) {
            if (parseInt(k, 10)+'' === k) {
              retObj[ct++] = args[i][k];
            } 
            else {
              retObj[k] = args[i][k];
            }
          }
        }
      }
    }
    return retObj;
  }
};

Drupal.content_podgroup._copyObject = function(oldObj) {
  var self = Drupal.content_podgroup;

  var newObj = (oldObj instanceof Array) ? [] : {};
  for (i in oldObj) {
    if (i == 'clone') continue;
    if (oldObj[i] && typeof oldObj[i] == "object") {
      newObj[i] = self._copyObject(oldObj[i]);
    }
    else {
      newObj[i] = oldObj[i];
    }
  }return newObj;
};
    
Drupal.content_podgroup._log = function(message) {
  var self = Drupal.content_podgroup;

  if (self.debug) {
    try {
      console.log(message);
    } catch(er){
      try {
        window.opera.postError(a);
      } catch(er) {
        // No console avaliable. put 
        // alert(a) here or write to a document node or just ignore
      }
    }
  }
};

Drupal.content_podgroup._checkIfReadyToShow = function() {
  var self = Drupal.content_podgroup;

  // Todo: Change the condition to a callback ex http://wiki.moxiecode.com/index.php/TinyMCE:API/tinymce.Editor/onInit
  if (Drupal.wysiwyg.instances[podgroup.podgroupShowConditional].editor != "tinymce" || (Drupal.wysiwyg.instances[podgroup.podgroupShowConditional].editor == "tinymce"
    && tinyMCE && tinyMCE.editors && tinyMCE.editors[podgroup.podgroupShowConditional] && tinyMCE.editors[podgroup.podgroupShowConditional].initialized)) {

    // Simulate a click on the configure link to pop open the configure dialog box
    self.podgroupToShow.click();

    // Clear drop lock now that we have returned from the ajax
    self.dropFlag = false;

  }
  else {
    setTimeout(self._checkIfReadyToShow, 100);
  }
};

Drupal.content_podgroup.inputMonitor = function() {
  var self = Drupal.content_podgroup;

  var field1 = jQuery("input[name='form_build_id']");
  var field2 = jQuery("input[name='form_token']");
  var field3 = jQuery("input[name='form_id']");
  var totalLength = field1.length+field2.length+field3.length;
  var parent = "";

  field1.parents().each(function(el) {
    $el = jQuery(el);
    parent += "> #" + $el.attr('id') + "." + $el.attr('class') + " ";
  });

  if (parent != self.hiddenFieldsParent) {
    if (typeof console != "undefined") {
      if (typeof console.debug != "undefined") {
        console.debug("Hidden fields moved to:");
        console.debug(field1.parents());
      }
    }

    self.hiddenFieldsParent = parent;
  }

  if (totalLength < self.hiddenFields) {
    alert("Misplaced the hidden fields.");
    self.hiddenFields = totalLength;
  }
}

Drupal.content_podgroup.initInputMonitoring = function() {
  var self = Drupal.content_podgroup;

  var field1 = jQuery("input[name='form_build_id']");
  var field2 = jQuery("input[name='form_token']");
  var field3 = jQuery("input[name='form_id']");
  var totalLength = field1.length+field2.length+field3.length;

  if (totalLength > 0) {
    var parent = "";
    field1.parents().each(function(el) {
      parent += "> " + el.classname + " ";
    });

    if (typeof console != "undefined") {
      if (typeof console.debug != "undefined") {
        console.debug("Monitoring hidden fields. Initial parent:");
        console.debug(field1.parents());
      }
    }

    self.hiddenFields = totalLength;
    self.hiddenFieldsParent = parent;
    setInterval(self.inputMonitor, 500);
  }
}
