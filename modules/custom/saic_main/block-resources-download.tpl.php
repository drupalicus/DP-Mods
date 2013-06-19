<?php if(isset($_COOKIE['download_access']))  { ?>
  <div class="box shade">
    <h3>Download This Document</h3>
    <p>Thanks for registering for the SAIC Resource Center. Please click the link below to download this document.</p>
    <p class="actionlink"><a href="<?php print $download_link ?>">Download Now »</a></p>
  </div>
<?php } else { ?>
  <div class="box alert">
    <h3>Register Today To Download This Document</h3>
    <p>To download this document and gain access to other materials from SAIC's industry experts, register today!</p>
    <p class="actionlink"><a href="<?php print $download_link ?>">Register Now »</a></p>
  </div>
<?php } ?>
