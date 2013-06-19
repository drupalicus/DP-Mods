<style type="text/css">

  body {
    margin:0px;
  }
  #inner_content_container {
      display: inline;
      font-size: 75%;
      line-height: 1.5em;
  }

  .center {
      text-align: center;
  }
  .column h3 {
      font-size: 15px;
  }

  .box h3 {
      font-size: 130%;
      font-weight: bold;
      margin-bottom: -3px;
      margin-left: 12px;
  }

  h3 {
      color: #006BB5;
      font-size: 125%;
      font-weight: bold;
      margin: 10px 0 2px;
      padding: 0;
  }

  .box.shade {
      background: none repeat scroll 0 0 #F9FCFF;
 }
  .box {
      border: 1px solid #BCD3EF;
      color: #585858;
      font-size: 90%;
      line-height: 1.545em;
      margin-top:20px
      padding: 0 0 12px;
      width: 198px;
  }
  .column p {
      font-size: 12px;
      line-height: 1.5em;
      margin: 0;
  }

  .column p, .column dl, .column multicol {
      display: block;
      margin: 1em 0;
  }

  .box p {
      padding: 10px 12px 0 !important;
  }
	.form-row {margin: 0 0 9px 12px}
	input.name, input.email, select.areas {border-top: 1px solid #b4b4b4; border-right: 1px solid #e4e4e4; border-bottom: 1px solid #e4e4e4; border-left: 1px solid #b4b4b4; background: #fff; padding:3px; width:164px;}
	select.areas {width:172px}
	p.center {margin:10px 0 6px 0;}
</style>

<div id="inner_content_container">
<div id="content" class="column">

 <script type="text/javascript">
	/*This array is used to populate the variables used by sitecatalyst
	Order of variable assignment is:
	s.prop1, s.prop2, s.prop3, s.prop4, s.prop5, s.events, s.products, s.eVar1, s.eVar2, s.eVar3, s.eVar4, s.eVar5*/
	var arrSiteCatalystSetUp = new Array('','','','','','event1','','Career: Mailing List Signup','','','','');

	function validate_form() {
	var reg = /^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/;
	valid = true;
	if (document.getElementById('name').value == "" ) {
		alert ('Your name is required.');
		valid = false;
	}
	if(reg.test(document.getElementById('irhddj-irhddj').value) == false) {
		alert('A valid email address is required.');
		valid = false;
	}
	if (document.getElementById('areas').value == "" ) {
		alert ('An area of interest is required.');
		valid = false;
	}		
	return valid; 
}
</script>


<div class="box shade" style="text-align:left; margin: 0px; padding: 0px;">
  <h3>Stay Connected</h3>
  <p style="margin-bottom:14px">Subscribe to our Talent Community to hear about career opportunities.</p>
  <form name="subForm" id="subForm" method="post" action="http://scienceapplications.createsend.com/t/r/s/irhddj/" onsubmit="return validate_form();">
      <div class="form-row">

          <label class="dialog-label" for="name">Your Name</label>
          <input name="cm-name" class="name" id="name" type="text" value="" tabindex="4" />
      </div>  
      <div class="form-row">
          <label class="dialog-label" for="email">Email Address</label>
          <input name="cm-irhddj-irhddj" class="email" id="irhddj-irhddj" type="text" value="" tabindex="5" />
      </div>
      <div class="form-row">

          <label class="dialog-label" for="areas">Area of Interest</label>
          <select name="cm-fo-wwv" class="areas" id="areas" tabindex="6" />
              <option selected value="">Please Select...</option>
              <option value="101679">Administrative</option>
              <option value="101680">Business Development</option>
              <option value="101681">Contracts/Pricing/Procurement</option>

              <option value="101682">Customer Logistics, Operations, and Planning</option>
              <option value="101683">Engineering</option>
              <option value="101684">Facilities/Security</option>
              <option value="101685">Finance/Accounting/Audit</option>
              <option value="101686">HR/Communications/Training</option>
              <option value="101687">Information Technology</option>

              <option value="101688">Intelligence and Defense Analysis</option>
              <option value="101689">Program and Project Management</option>
              <option value="101690">Science and Health</option>
          </select>
      </div>        
	  <p class="center"><input type="image" src="../images/btn_subscribenow2.png" id="submit" value="Submit" tabindex="8"></p>
  </form>
</div>
