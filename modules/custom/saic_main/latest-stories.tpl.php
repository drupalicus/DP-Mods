<div id="latestnews">
    <?php if($show_title) { ?> <h3><?php print $title ?></h3> <?php } ?>
    <ul>
    <?php foreach($data as $index => $story) {
      echo '<li><a href="'.$story['path'].'"><div class="item">'.$story['title'].'</div><div class="date">'.$story['date'].'</div></a></li>';
    }
    ?>
    </ul>
</div>
