<script type="text/javascript">
   $(document).ready(function(){
       $("tr.link").mouseover(function(){$(this).addClass("over");}).mouseout(function(){$(this).removeClass("over");});
       $("tr.link").click(function () {window.location = $(this).find("a:first").attr("href");});
     });
</script>


<table width="100%" cellspacing="0" summary="" class="simple">
<thead>
<tr>
	<th width="160" align="left" scope="col"><?php print $section->name; ?></th>
    <th width="100" scope="col">&nbsp;</th>
    <th scope="col">&nbsp;</th>
</tr>
</thead>

<tbody>
  <?php print $content; ?>
</tbody>
</table>
