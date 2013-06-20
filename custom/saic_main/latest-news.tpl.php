<div id="latestnews">
    <h3><?php print $title ?></h3>
    <ul>
    <?php foreach($data as $index => $story) {
      echo '<li><a href="'.$story['path'].'"><div class="item">'.$story['title'].'</div><div class="date">'.$story['date'].'</div></a></li>';
    }
    ?>
    </ul>
</div>
