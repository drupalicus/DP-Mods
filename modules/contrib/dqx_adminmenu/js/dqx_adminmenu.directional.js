
(function(){

  var d = Drupal.dqx_adminmenu;
  d.directional = {};


  d.directional.EventHistory = function() {

    var delay = 300;
    var history = [];

    var cleanHistory = function() {
      history = history.slice(-30);
      var cut_time = d.getMillis() - delay - delay;
      for (var i = 0; i < history.length; ++i) {
        if (history[i].t >= cut_time) break;
      }
      history = history.slice(i);
    };

    this.registerEvent = function($element, x, y) {
      var event = {'$element':$element, x:x, y:y, t:d.getMillis()};
      history.push(event);
      latest = event;
      cleanHistory();
    };

    this.lookBack = function(t) {
      for (var i = history.length - 1; i >= 0; --i) {
        if (history[i].t < t) {
          return history[i];
        }
      }
      return false;
    };

    this.isVertical = function() {
      var n = history.length;
      if (n < 3) {
        return true;
      }
      var h0 = history[n-1];
      var h1 = history[n-2];
      var h2 = this.lookBack(h0.t - 20);
      var dx1 = Math.abs(h0.x - h1.x);
      var dx2 = Math.abs(h0.x - h2.x);
      var dy1 = Math.abs(h0.y - h1.y);
      var dy2 = Math.abs(h0.y - h2.y);
      // console.log(dy, dx, dxx, dt);
      return (dy1 > dx1 && dy2 > 2 * dx2);
    };

    this.isHorizontal = function() {
      var n = history.length;
      if (n < 2) {
        return true;
      }
      var dx = history[n-1].x - history[n-2].x;
      var dy = history[n-1].y - history[n-2].y;
      var dt = history[n-1].t - history[n-2].t;
      return Math.abs(dx) > Math.abs(dy);
    };
  };


  d.MouseEngine_directional = function() {

    // default delay duration
    if (typeof delay != 'number') {
      delay = 600;
    }

    var history = new d.directional.EventHistory();

    var timer;
    var $recentElement = true;

    /**
     * @param $element
     *   The li, tr, #dqx_adminmenu or body element that is being hovered.
     * @param x, y
     *   x and y mouse position.
     */
    this.mouseMove = function($element, x, y) {
      history.registerEvent($element, x, y);
      if (!d.compareElements($element, $recentElement)) {
        $recentElement = $element;
        clearTimeout(timer);
        var hard = false;
        if ($element && $element.is('.expandable')) {
          var depth = d.countParentItems($element);
          switch (depth) {
            case 0:
              hard = true;
              break;
            case 1:
            default:
              hard = history.isVertical();
          }
        }
        var immediate = d.focusItem($element, hard);
        if (!immediate) {
          setTimeout(function(){
            d.focusItem($recentElement, true);
          }, delay);
        }
      }
    };
  };


  d.behaviors.mouse = function(context, settings, $divRoot) {
    var mouse_engine = new d.MouseEngine_directional();
    d.attachMouseEngine($divRoot, mouse_engine);
  };

})();
