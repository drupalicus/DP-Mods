
Drupal.dqx_adminmenu = {behaviors: {}};

(function(){

  var d = Drupal.dqx_adminmenu;


  d.getMillis = function() {
    return (new Date()).getTime();
  };


  d.compareElements = function($ele1, $ele2) {
    if ($ele1 == null || $ele2 == null || typeof $ele1 != 'object' || typeof $ele2 != 'object') {
      return $ele1 == $ele2;
    }
    if ($ele1.length != $ele2.length) {
      return false;
    }
    for (var i = 0; i < $ele1.length; ++i) {
      if ($ele1[i] != $ele2[i]) {
        return false;
      }
    }
    return true;
  };


  d.countParentItems = function($item) {
    var n_parents;
    if ($item && $item.length) {
      n_parents = 0;
      $item = $item.parent();
      while ($item && $item.length && !$item.is('#dqx_adminmenu, body')) {
        if ($item.is('li, tr')) {
          ++n_parents;
        }
        $item = $item.parent();
      }
    }
    return n_parents;
  };


  d.init = function($divRoot) {
    $('body').addClass('dqx_adminmenu');
    for (var f in d.behaviors) {
      if (typeof d.behaviors[f] == 'function') {
        d.behaviors[f]($divRoot, Drupal.settings.dqx_adminmenu, $divRoot);
      }
    }
  };


  d.behaviors.fixRedirectDestination = function(context, settings, $divRoot) {
    $('a.dqx_adminmenu-redirect', $divRoot).each(function(){
      var href = this.href;
      if (href.split('?').length < 2) {
        this.href += '?' + settings.destination;
      }
      else if (href.split('?destination=').length > 1) {
        // do nothing
      } else if (href.split('?')[1].split('&destination=').length > 1) {
        // do nothing
      } else {
        this.href += '&' + settings.destination;
      }
    });
  };


  /**
   * @param $item
   *   The li or tr element to activate.
   */
  d.focusItem = function($item, hard) {

    if (!$item || !$item.length || !$item.is('li, tr')) {
      if (hard) {
        d.unfocusAll();
      }
    }
    else {
      if (hard || $item.is('.expandable')) {
        $siblings = $item.siblings('li, tr');
        var $open_sibling_submenus = $('ul.show, table.show', $siblings);
        if (hard || !$open_sibling_submenus.length) {
          $open_sibling_submenus.removeClass('show');
          var $submenu = $('> ul, > td > ul, > td > div > ul, > table, > td > table, > td > div > table', $item);
          $submenu.addClass('show');
          $('ul.show, table.show', $submenu).removeClass('show');
          hard = true;
        }
      }

      // trickle up
      $element = $item.parent();
      while (!$element.is('#dqx_adminmenu')) {
        if ($element.is('li, tr')) {
          // hide siblings
          $siblings = $element.siblings('li, tr');
          $('ul.show, table.show', $siblings).removeClass('show');
        }
        else if ($element.is('ul, table')) {
          // show parent
          $element.addClass('show');
        }
        $element = $element.parent();
      }
    }

    return hard;
  };


  d.unfocusAll = function() {
    $('#dqx_adminmenu ul.show, #dqx_adminmenu table.show').removeClass('show');
  }


  d.MouseEngine_simple = function() {
    /**
     * @param $element
     *   The li or tr element that is being hovered, or null for body hover.
     * @param x, y
     *   x and y mouse position.
     */
    this.mouseMove = function($element, x, y) {
      if ($element) {
        if ($element.is('.expandable')) {
          d.focusItem($element, true);
        }
      }
      else {
        d.unfocusAll();
      }
    };
  };


  /**
   * This one waits a bit, before it closes a submenu.
   *
   * @param delay
   *   The delay in milliseconds
   */
  d.MouseEngine_superfish = function(delay) {

    // default delay duration
    if (typeof delay != 'number') {
      delay = 2600;
    }

    var timer;
    var $recentElement = true;

    /**
     * @param $element
     *   The li, tr, #dqx_adminmenu or body element that is being hovered.
     * @param x, y
     *   x and y mouse position.
     */
    this.mouseMove = function($element, x, y) {
      if (!d.compareElements($element, $recentElement)) {
        $recentElement = $element;
        clearTimeout(timer);
        var hard = $element && $element.is('.expandable');
        var immediate = d.focusItem($element, hard);
        if (!immediate) {
          setTimeout(function(){
            d.focusItem($recentElement, true);
          }, delay);
        }
      }
    };
  };


  d.getItem = function($element) {
    var $item = false;
    while ($element.length && !$element.is('li, tr, #dqx_adminmenu, body')) {
      $element = $element.parent();
      // if ($element.is('lis
    }
    return $element;
  };


  d.attachMouseEngine = function($divRoot, mouse_engine) {
    $('li, tr', $divRoot).mousemove(function(event) {
      event.xyz = 'li / tr';
      $element = $(this);
      mouse_engine.mouseMove($element, event.pageX, event.pageY);
      event.stopPropagation();
    });
    $('ul, table', $divRoot).mousemove(function(event) {
      event.xyz = 'ul / table';
      event.stopPropagation();
    });
    $divRoot.mousemove(function(event) {
      event.xyz = '$divRoot';
      event.stopPropagation();
    });
    $('body').mousemove(function(event) {
      mouse_engine.mouseMove(null, event.pageX, event.pageY);
    });
  };


  d.behaviors.mouse = function(context, settings, $divRoot) {
    var mouse_engine = new d.MouseEngine_superfish();
    d.attachMouseEngine($divRoot, mouse_engine);
  };


  d.behaviors.tooltip = function(context, settings, $divRoot) {
    var $tooltip = $('<div id="dqx_adminmenu-tooltip">bla');
    // $tooltip.appendTo($divRoot);
    $tooltip.css({display:'none', position:'fixed', bottom:0, right:0, top:'auto', left:'auto'});
    $('li a, tr a').each(function(event){
      var $link = $(this);
      var title = $link.attr('title');
      $link.attr('title', null);
      $link.mousemove(function(event){
        $tooltip.css('display', 'block');
        $tooltip.html(title);
        event.dqx_adminmenu_tooltip = true;
      });
    });
    $('body').mousemove(function(event){
      $tooltip.css('display:none;');
    });
  };


  d.behaviors.activePage = function(context, settings, $divRoot) {
    var path = document.location.pathname;
    var fragments = path.split('/');
    var partials = [fragments[0]];
    var matches = [[]];
    for (var i = 1; i < fragments.length; ++i) {
      partials[i] = partials[i-1] + '/' + fragments[i];
      matches[i] = [];
    }
    $('li a, tr a', $divRoot).each(function(){
      var link = this;
      var link_fragments = link.pathname.split('/');
      if (link.pathname == partials[link_fragments.length - 1]) {
        matches[link_fragments.length - 1].push(link);
      }
    });
    for (var i = fragments.length - 1; i >= 0; --i) {
      if (matches[i].length) {
        break;
      }
    }
    if (i >= 0) {
      for (var j = 0; j < matches[i].length; ++j) {
        var $link = $(matches[i][j]);
        if (i == fragments.length - 1) {
          $link.addClass('active');
        }
        for (var $element = $link; $element && !$element.is('#dqx_adminmenu'); $element = $element.parent()) {
          if ($element.is('li, tr, td, a, ul, table')) {
            $element.addClass('active-trail');
            $('> a, > span > a, > div > a', $element).addClass('active-trail');
          }
        }
      }
    }
  };

})();

$(function(){
  // stuff to run when the page loads.
  $.ajax({
    url: Drupal.settings.dqx_adminmenu.json_url,
    dataType: 'json',
    success: function(data) {
      if (data.html) {
        var divRoot = $('<div>');
        divRoot.attr('id', 'dqx_adminmenu-wrapper');
        divRoot.html(data.html);
        divRoot.prependTo('body');
        Drupal.dqx_adminmenu.init(divRoot);
        console.log(divRoot);
      }
    }
  });
});

