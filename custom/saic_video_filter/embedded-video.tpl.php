<div class="video">
  <div class="video-thumb">
    <?php print l(theme('imagecache', 'video_embedded_thumb', ($video->field_video_thumbnail[0]['filepath'] ? $video->field_video_thumbnail[0]['filepath'] : '/sites/all/themes/saic/images/default.jpg'), $video->title, $video->title), 'partials/video/' . $video->nid, array('query' => saic_get_args(), 'html' => TRUE, 'attributes' => array('class' => 'vc_video_list_item_thumb vc_play_hover_large video_popup', 'title' => 'View this video'))) ?>
  </div>					
  <div class="video-details">
	<a class="video-title video_popup" href="/partials/video/<?php print $video->nid ?>"><?php print $video->title ?></a>
    <span class="video-duration"><?php print theme('cck_time', $video->field_video_length[0]) ?> &bull; </span> 
    <span class="video-rating">
    <?php print fivestar_widget_form($video); ?>
    </span>
  </div>
</div>
