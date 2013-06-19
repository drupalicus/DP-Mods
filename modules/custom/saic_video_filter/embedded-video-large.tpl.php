<?php 
  $serverName = $GLOBALS['base_url'];

  if($show_title){
    $title = '<h6 style="padding:0;margin:0 10px;font-weight:normal;color:#782f97;font-size:20px;font-family:Arial, Helvetica, sans-serif;">' . $video->title . '</h6>';
  }

  if($show_more_link){
    $disable_embedViewMore = "false";
  }
  else{
    $disable_embedViewMore = "true";
  }

  if($show_border){
    $border_style = 'margin:0 0 10px;padding:5px 0 0;width:500px; border:1px solid #d3d3d3;';
  }
  else{
    $border_style = 'margin:0 0 0px;padding:0px 0 0;width:500px;';
  }
?>

<div style="<?php print $border_style;?>">
  <?php print $title; ?>
  <object height="300" width="5000">
    <param name="movie" value="<?php print $serverName; ?>/sites/all/themes/saic/swfs/player.swf"></param>
    <param name="allowScriptAccess" value="always"></param><param name="wmode" value="transparent"></param>
    <param name="allowFullScreen" value="true"></param>
    <param name="flashvars" value="baseURL=http://www2.saic.com&xmlPath=<?php print $serverName; ?>/media/<?php print $video->nid ?>/detail.xml"></param>
    <embed src="<?php print $serverName; ?>/sites/all/themes/saic/swfs/player.swf?baseURL=http://www2.saic.com&xmlPath=<?php print $serverName; ?>/media/<?php print $video->nid ?>/detail.xml" type="application/x-shockwave-flash" allowfullscreen="true" allowscriptaccess="always" scale="noscale" wmode="transparent" width="5000" height="300"></embed>
  </object>
</div>
