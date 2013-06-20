<?php 


function make_paging($max='',$limit='12',$page='0',$url='#',$max_links = '10'){
    $back = -1; 
    $next = 2;
     
    $return_html = '';
    $page_name = $url;
    if($max > $limit ){ 
        $return_html =  '<ul class="pager">'; 
        if($back >=0)
            $return_html .=  '<li><a onclick="com.saic.media_library.change_page(\''.$back.'\',\'right\'); return false;" id="Prev" href="'.$url.'">Prev</a></li>'; 
        else
            $return_html .=  '<li><a style="display:none;" onclick="com.saic.media_library.change_page(\''.$back.'\',\'right\'); return false;" id="Prev" href="'.$url.'">Prev</a></li>'; 
        $i=0;
        $l=1;
        for($i=0;$i < $max;$i=$i+$limit){
            if($max_links <= $l)
                break;
            if($i != $page)
                $return_html .='<li><a onclick="com.saic.media_library.change_page(\''.$l.'\',false); return false;" id="'.$l.'" href="'.$url.'">'.$l.'</a></li>';
            else  
                $return_html .= '<li class="active"><a onclick="com.saic.media_library.change_page(\''.$l.'\',false); return false;" id="'.$l.'" href="#">'.$l.'</li>';         
            $l=$l+1;
        }
        
        if($next < $max) 
            $return_html .= '<li><a onclick="com.saic.media_library.change_page(\''.$next.'\',\'left\'); return false;" id="Next" href="'.$url.'">Next</a></li>';
        $return_html .= "</ul>";
        return $return_html;   
    }

    return $return_html;  
}


// $Id: saic_media_menu

function saic_media_menu_js() {

   // Build in clause to filter out the type of node you want the result set for
   $types = "";
   $media_types = $_GET['type'];

   if(!$_GET['type'])
      $types = " AND n.type IN ('video','audio','ddp_image') ";
   else if( !is_array($media_types) || count($media_types) == 0   || ( count($media_types) == 1 && $media_types[0] == 'All' ) )
       $types = " AND n.type IN ('video','audio','ddp_image') ";
    else{
       foreach($media_types as $position => $type){
         if($type == 'video')
           $type = 'video';
         else if($type == 'ddp_image' || $type == 'image')
           $type = 'ddp_image';
         else if($type == 'all')
           continue;

         if($type =='audio' || $type =='video' || $type =='ddp_image')
         $all_types[] = $type;
      }
      $media  = implode(",", $all_types);
      $node_types = str_replace(",", "','", $media);
      $types = " AND n.type IN ('$node_types') ";
   }


   $channels = $_GET['channel'];

   if(!$_GET['channel'])
      $channel_where = " ";
   else {
       foreach($channels as $position => $channel){
         $all_channels[] = ((int) $channel);
      }

      $channel_imp = implode(",", $all_channels);
      $node_channels = str_replace(",", "','", $channel_imp);
      $channel_where  = " AND td.tid IN ('$node_channels') ";
   }


   //Get a list of each type to cross check to return 0 if no results are below
   $all_types = "
   SELECT 
     td.tid as id
   FROM
     term_data td
   WHERE
     td.vid = 2
   ";
  $result = db_query($all_types);
  $all_menus = array();
  while($row = db_fetch_array($result)) {
    $all_menus[$row['id']] = $row;
  }


   //Get a count of each type to refresh the menu
   $get_type_count = "
   SELECT 
     td.tid as id,
     COUNT(distinct(n.nid)) as count
   FROM
     node n,
     term_data td,
     term_node tn,
     content_field_display_wall tw
   WHERE
     tn.tid = td.tid
   AND
     tn.vid = n.vid
   AND
     td.vid = 2
   AND
     n.status = 1 
   AND
     tw.nid = n.nid
   AND
      tw.field_display_wall_value = 1
   $types 
  GROUP BY
    td.tid
  ";
 
  $result_count = 0;
  $found_results = 0;
  $result = db_query($get_type_count);
  $menu_items = array();
  while($row = db_fetch_array($result)) {
    $menu_items[] = $row;
    $menu_items_found[$row['id']] = $row['id'];
    $result_count += $row['count'];
  }

  foreach($all_menus as $key => $value){
   if(!isset($menu_items_found[$value['id']])){
      $tmp_row['id'] = $value['id'];
      $tmp_row['count'] = 0;
      $menu_items[] = $tmp_row;
   }

  }

   $get_paging_count = "
   SELECT 
     COUNT(distinct(n.nid)) as count
   FROM
     node n,
     term_data td,
     term_node tn,
     content_field_display_wall tw
   WHERE
     tn.tid = td.tid
   AND
     tn.vid = n.vid
   AND
     td.vid = 2
   AND
     n.status = 1 
   AND
     tw.nid = n.nid
  AND
     tw.field_display_wall_value = 1
   $types
   $channel_where
  GROUP BY
    n.nid
  ";
  
  $get_type_count = 0;
  $result = db_query($get_paging_count);
  while($row = db_fetch_array($result)) {
    $get_type_count += $row['count'];
  }

   if($_GET['view'] != 'list')
     $per_page = 13;
   else
     $per_page = 12;

  $maxp = ceil($get_type_count / $per_page);
 
   if($maxp < 10)
      $lastp = $maxp;
   else
      $lastp = 10;

  $menu_items['items'] = $get_type_count;
  $menu_items['maxp'] = $maxp;
  $menu_items['lastp'] = $lastp;
  $menu_items['paging'] = make_paging($get_type_count,$per_page ,1,'#', '6');

  return drupal_json($menu_items);
}
