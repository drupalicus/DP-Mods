jQuery(document).ready(function() {

  Drupal.content_type_tag = new Object();
  Drupal.content_type_tag.toggleTagFields = function(ref) {
    $tweettags = $(ref).parent().parent().find('.tweet-tags-wrapper');
    if (ref.value == 'tweet') {
      $tweettags.show();
    }
    else {
      $tweettags.hide();
    }
  }

  // 34827 Display 'Tweet Hashtags' when 'Tweets' content type is selected on press-kit node form
  //jQuery('#field-press-kit-content-type-items .content-type').bind('change',function() {
  //  Drupal.content_type_tag.toggleTagFields(this);
  //});

  // Same as above just... lets make it right from the start
  jQuery('#field-press-kit-content-type-items .content-type').each(function() {
    Drupal.content_type_tag.toggleTagFields(this);
  });

});

