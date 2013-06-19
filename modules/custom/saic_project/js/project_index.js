/**
 *  Project index page
 *  <p>This object holds all the functions for the Project Index and Project Filter</p>
 *  @constructor
 *  @author Michael Turnwall - Digitaria, Inc.
 *  Copyright (c) 2011 Digitaria, Inc. 
 */

var Projects = (function () {
    /**
     *  retrieves css for a given element
     *  @private
     *  @param {DOM Node} el the element to find the style from
     *  @param {String} style the actual style to get such as padding, margin, postion, etc
     *  @returns {String} the value of the style or an error message
     */
    function getStyle(el, style) {
        var styled;
        if (typeof el !== "object") {
            el = document.getElementById(el);
        }
        if (el.currentStyle) {  // IE
            styled =  (el.currentStyle[style]);
        } else if (window.getComputedStyle) {  // everyone else
            styled =  (document.defaultView.getComputedStyle(el,null).getPropertyValue(style));
        }
        return (styled) ? styled : "Error: Sorry, " + style + " could not be found";
    }
    /**
     *  finds the position of a DOM Node either relative to it's first offset parent or the window
     *  @private
     *  @param {DOM Node} el the element to find the style from
     *  @param {Boolean} [offset='false'] if set to true, position is based off of elements offset parent
     *  @returns {Object} element's position represented by an object, pos.x and pos.y
     */
    function findPosition(el, offset) {
        var pos = {
            x: 0,
            y: 0 
        };
        if (el.offsetParent) {
            do {
                pos["x"] += el.offsetLeft;
                pos["y"] += el.offsetTop;
                if (offset) {
                    if (getStyle(el.offsetParent, 'position') == 'relative') {
                        break;
                    }
                }
                el = el.offsetParent;
            } while(el);
        }
        return pos;
    }
    function getViewport() {
        var viewport = [];
        // standards compliant browsers
        if(window.innerHeight) {
            viewport["width"] = window.innerWidth;
            viewport["height"] = window.innerHeight;
        }
        // IE6 in standards mode. IE6 in quirks mode won't work
        else if(document.documentElement.clientHeight) {
            viewport["width"] = document.documentElement.clientWidth;
            viewport["height"] = document.documentElement.clientHeight;
        }
        return viewport;
    }
    function getScrollLength() {
        offset = [];
        if (self.pageXOffset || self.pageYOffset) {
            offset["x"] = self.pageXOffset;
            offset["y"] = self.pageYOffset;
        }else if ((document.documentElement && document.documentElement.scrollLeft)||(document.documentElement && document.documentElement.scrollTop)) {
            offset["x"] = document.documentElement.scrollLeft;
            offset["y"] = document.documentElement.scrollTop;
        }
         else if (document.body) {
            offset["x"] = document.body.scrollLeft;
            offset["y"] = document.body.scrollTop;
        }
        return offset;
    }
    return {
        timer: false,
        delay: 250,
        findElementPos: function (el, offset) {
            return findPosition(el, offset);
        },
        show: function (el) {
            var left, topOffset, $_popup, $_parent, popupHeight, offsetPos, truePos, viewport, contentArea, scrollLength,
                popupWidth, side;
            
            topOffset = 0;
            $_popup = $('.project-popup', el);
            $_parent = $_popup.parents('#content-center');
            popupHeight = $_popup.outerHeight();
            offsetPos = this.findElementPos(el, true);
            truePos = this.findElementPos(el);
            viewport = getViewport();
            contentArea = {
                width: $_parent.width(),
                height: $_parent.height()
            };
            scrollLength = getScrollLength();
            popupWidth = $_popup.outerWidth();
            
            //  if combination of the left pos, hover element width, and popup width is less than the main area
            //  then put on right side
            if (offsetPos.x + el.offsetWidth + popupWidth < contentArea.width) {
                left = offsetPos.x + el.offsetWidth;
                side = 'right';
            } else {
                left = offsetPos.x - popupWidth; // subtract 20 to compensate for the shadow
                side = 'left';
            }
            
            // make sure popup doesn't go off the bottom of the page
            if ((truePos.y + popupHeight) > (viewport['height'] + scrollLength['y'])) {
                topOffset = (truePos.y + popupHeight) - (viewport['height'] + scrollLength['y']);
            } 
            $_popup.css({
                top: offsetPos.y - topOffset - 10,
                left: left
            });

            if ($_popup.css('display') != 'block') {
                el.className += ' active';
                $_popup.animate({
                    left: (side == 'right') ? (left + 10) : (left - 10),
                    opacity: 'toggle'
                }, 'fast');
            }
        },
        hide: function (el) {
            el.className = el.className.replace('active', '');
            $('.project-popup', el).removeClass('active').hide();
        },
        clearTimer: function () {
            clearTimeout(this.timer);
        },
        /**
         *  Updates the Criteria select menu in the Filter box depending on the user's
         *  selection in the Filter By select menu. The Criteria select menu will always
         *  have "All" option.
         *  @param filterId value attribute of the option chosen in the Filter By select menu. Should
         *                  always be a number.
         *  @author Michael Turnwall
         */
        updateFilter: function (filterId) {
            var $_criteria = $('#edit-child-tid'),
                grandChildren,
                children;
            $_criteria.empty();
            // there should always be an All option
            $_criteria.append('<option value="all">- All -</option>');
            if (filterId != 'all') {
                children = Drupal.settings.project_term_tree[filterId].children;
                for (var child in children) {
                    $_criteria.append('<option value="' + children[child].tid + '">' + children[child].name + '</option>');
                }
            } else {
                children = Drupal.settings.project_term_tree;
                for (var child in children) {
                    grandChildren = children[child].children;
                    for (var grandChild in grandChildren) {
                        $_criteria.append('<option value="' + grandChildren[grandChild].tid + '">' + grandChildren[grandChild].name + '</option>');
                    }
                }
            }
        },
        init: function (selector) {
            var obj = this;
            $(selector).hover(function () {
                var el = this;
                obj.clearTimer.call(obj);
                obj.timer = setTimeout(function () {
                    obj.show.call(obj, el);
                }, obj.delay);
            }, function () {
                obj.clearTimer.call(obj);
                obj.hide.call(obj, this);
            });
        }
    };
})();
$(document).ready(function () {
    Projects.init('.view-project-index .views-row');
    $('.view-id-featured_projects .views-row')
        .hover(function () {
            $(this).addClass('featuredHoverOn');
        }, function () {
            $(this).removeClass('featuredHoverOn');    
        })
        .bind('click', function () {
            window.location = $(this).find('strong a').attr('href');
            return false;
        });
});
