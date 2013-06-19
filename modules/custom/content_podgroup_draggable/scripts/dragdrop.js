var dragDropChanged=false;

function createCookie(name,value,days) {
	if (days) {
		var date = new Date();
		date.setTime(date.getTime()+(days*24*60*60*1000));
		var expires = "; expires="+date.toGMTString();
	}
	else var expires = "";
	document.cookie = name+"="+value+expires+"; path=/";
}

function readCookie(name) {
	var nameEQ = name + "=";
	var ca = document.cookie.split(';');
	for(var i=0;i < ca.length;i++) {
		var c = ca[i];
		while (c.charAt(0)==' ') c = c.substring(1,c.length);
		if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
	}
	return null;
}

function identifyDraggables() {
	/* Identify all elements we want to apply drag behavior to */
	/* .list-group should also be in here but temporarily removed */
	jQuery('.banner, .faq-block, .faq-item, .header, .list-item, .list-group, .list-wrapper, .open-html, .side-by-side, .spotlight-group, .spotlight-wrapper, .tabs-container, .tab-pane').wrap('<div class="draggable"></div>');
	
	/* Add the drag controls to the top of them */
	jQuery('.draggable').prepend('<div class="drag-controls"><div class="drag-handle">Drag Handle</div><a href="#" class="drag-edit">Edit</a></div>');
	
	/* Ensure all draggables wrap elements with ids and have rels that point to those ids */
	jQuery('.draggable').each(function(index, el) {
		/* Find the element it's wrapping */
		var $_draggableFor=jQuery(jQuery(el).children().get(1));
		
		/* Set the rel to the id of the element it's wrapping */
    var id = $_draggableFor.attr('id');
		jQuery(el).attr('rel', id);

    //Set the href for the edit link
    var group_name = jQuery($_draggableFor.find('.cpd_group_name').get(0)).val();
    var delta = jQuery($_draggableFor.find('.cpd_delta').get(0)).val();
    var href = '/node/' + Drupal.settings.content_podgroup_draggable.nid + '/edit#' + group_name + '-' + delta;
    jQuery(el).find('.drag-edit').attr('href', href);
    
	});
}

function identifyDroppables() {
	/* Identify all the elements we want to allow dropping within */
    jQuery('.content-podgroup, #sidebar_left, #content, #sidebar_right, .faq-block, .list-group, .list-wrapper, .spotlight-wrapper, .spotlight-group, .tabs-container, .tab-pane').addClass('droppable');
	//jQuery('#sidebar_left, #content, #sidebar_right, .faq-block, .list-group, .list-wrapper, .spotlight-wrapper, .spotlight-group, .tabs-container, .tab-pane').addClass('droppable');
	
	jQuery('.droppable').each(function(index, el) {
		var $_el=jQuery(el);

    //Set the id of the droppable to the group_name|delta so the children know the parent's (this objects) values
		if ($_el.attr('id')=="") {
      var group_name = jQuery($_el.find('.cpd_group_name').get(0)).val();
      var delta = jQuery($_el.find('.cpd_delta').get(0)).val();
      $_el.attr('id', group_name + '|' + delta);
		}
	});
}

function bindDraggables() {
	var dragging=false;
	
	/* For all of the dragable elements */
	$('.draggable').each(function(index, el) {
		var $_el=$(el);
		/* Store the nearest parent of class droppable */
		var $_parentDroppable=jQuery($_el.parents('.droppable').get(0));
		
		/* Bind the mouseover and mouseout events to turn on/off the drag-hover state */
		$_el.mouseover(function(e) {
			if (!dragging) {
				e.stopPropagation();
				jQuery(this).addClass('drag-hover');
				jQuery(this).parents('.draggable').addClass('drag-hover-ancestor');
			}
		}).mouseout(function(e) {
			e.stopPropagation();
			jQuery(this).removeClass('drag-hover');
			jQuery(this).parents('.draggable').removeClass('drag-hover-ancestor');
		});
		
		/* Set up the dragging behavior */
		$_el.draggable({
			handle: '.drag-handle',
			helper: function() {
				/* Create the helper (the draggable element) */
				$('body').append('<div id="drag-helper">Drag and drop to any new blue target position</div>');
				return $('#drag-helper').get(0);
			},
			start: function(e, ui) {
				var $_siblingDraggables=$_el.parent().children('.draggable');
				
				dragging=true;
				
				/* Fade the dragged element */
				$_el.css('opacity', 0.2);
				
				/* Set the parent droppable to active */
				$_parentDroppable.addClass('drag-container-active');
				
				/* Add Drag Targets before the first sibling and after all siblings */
				jQuery($_siblingDraggables.get(0)).before('<div class="drag-target"><span>DROP ZONE</span></div>');
				$_siblingDraggables.after('<div class="drag-target"><span>DROP ZONE</span></div>');
		
				/* 
					For all of those drag targets,
					Set them up as droppables.
				*/
				jQuery('.drag-target').each(function(index, _dragTarget) {
					var $_dragTarget=jQuery(_dragTarget);
					$_dragTarget.droppable({
						drop: function(e, ui) {
							/* 
								When the element has been dropped on the drag target,
								move the element to right after it in the dom tree.
							*/
							$_dragTarget.after($_el);
							
							/* Raise the changed flag */
							dragDropChanged=true;
							jQuery('body').addClass('edit-mode-unsaved');
						},
						over: function() {
							/* Set the drag-over state */
							$_dragTarget.addClass('drag-target-active');
						},
						out: function() {
							/* Remove the drag-over state */
							$_dragTarget.removeClass('drag-target-active');
						}
					});
				});
			},
			stop: function(e, ui) {
				/* Drop the dragging flag */
				dragging=false;
				/* Set the opacity of the element being moved back to normal */
				$_el.css('opacity', 1);
				/* Remove all of the drag targets that we created */
				jQuery('.drag-target').remove();
				/* Remove the droppable-active class from the drop container */
				$_parentDroppable.removeClass('droppable-active');
			}
		});
		
	});
}

function buildChildMap() {
	var childMap={};
  var postArray = {};

  //add nid to the childMap  
  postArray['nid'] = Drupal.settings.content_podgroup_draggable.nid;
  postArray['podgroups'] = {};

	jQuery('.draggable').each(function(index, el) {
		var parent=jQuery(jQuery(el).parents('.droppable').get(0)).attr('id');
    //if group has no parent, its parent must be the root
		if (typeof parent == "undefined") {
      parent = 'parent';
    }	

		if (typeof postArray['podgroups'][parent] == "undefined") {
			postArray['podgroups'][parent]=[];
		}
    var rel = jQuery(el).attr('rel');

    //populate a row for each podgroup
    var row = {};
    row['id'] = rel;
    row['region'] = jQuery(jQuery(el).find('.cpd_region').get(0)).val();
    row['group_name'] = jQuery(jQuery(el).find('.cpd_group_name').get(0)).val();
    row['delta'] = jQuery(jQuery(el).find('.cpd_delta').get(0)).val();

		postArray['podgroups'][parent].push(row);
	});

  jsonString = JSON.stringify(postArray);

  //create wrapper for jsonString
  var jsonPost = {};
  jsonPost['podgroups'] = jsonString; 

  //make ajax call to save node  
  jQuery.post('/content_podgroup_draggable/js/submit', jsonPost);
  
}

function initDragDropMoveDragDialog() {
	jQuery('#edit-side').draggable({
		handle: '#edit-side-main',
		stop: function(e, ui) {
			jQuery('#edit-side').css('left', 0);
		}
	});
}

function initDragDrop() {
	var editModeCookie=readCookie('edit-mode');
	if (editModeCookie=="on") {
		jQuery('body').addClass('edit-mode-on');
	
		/* Identify all elements we want to apply drag behavior to */
		identifyDraggables();
		/* Identify all the elements we want to allow dropping within */
		identifyDroppables();
		/* For the elements we have now identified, set up the drag/drop behavior */
		bindDraggables();

		/* If there are unsaved changes, intercept exit events */
    window.onbeforeunload = function (e) {
			if (dragDropChanged) {
				return "You have not saved your new layout.";
			} else {
				return null;
			}
		}
	}
	
	jQuery('#edit-side-off').click(function(e) {
		e.preventDefault();
		createCookie('edit-mode', 'off', 30);
		document.location.reload();
	});
	
	jQuery('#edit-side-on').click(function(e) {
		e.preventDefault();
		createCookie('edit-mode', 'on', 30);
		document.location.reload();
	});
	
	jQuery('#edit-side-btn-save').click(function(e) {
		e.preventDefault();
		buildChildMap();
		dragDropChanged=false;
		jQuery('body').removeClass('edit-mode-unsaved');
	});
	
	jQuery('#edit-side-btn-cancel').click(function(e) {
		e.preventDefault();
		dragDropChanged=false;
		document.location.reload();
	});
	
	initDragDropMoveDragDialog();
}

jQuery(document).ready(function() {
	initDragDrop();
});