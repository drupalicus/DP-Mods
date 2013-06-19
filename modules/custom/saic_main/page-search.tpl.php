<script type="text/javascript"> 
 
 
$(document).ready(function(){
 
	//Hide (Collapse) the toggle containers on load
	$(".toggle_container").hide(); 
 
	//Switch the "Open" and "Close" state per click
	$("h3.trigger").toggle(function(){
		$(this).addClass("active");
		}, function () {
		$(this).removeClass("active");
	});
 
	//Slide up and down on click
	$("h3.trigger").click(function(){
		$(this).next(".toggle_container").slideToggle("normal");
	});
 
});
</script>
<style>
#content-center {
    font-size: 75%;
    line-height: 1.5em;
}
</style>
<h1>SAIC.com Advanced Search</h1>
<h2>Want more control over your search results? Use a combination of the options below to refine your search and get more accurate results.</h2>
<hr>
<h3>Find web pages that have...</h3>
<div id="cleanform">


<fieldset class="group first">
	<label for="allwords">All these words</label>
	<div class="field"><input type="text" value="" class="text full" id="ctl00_ContentPlaceHolder1_allwords" name="ctl00$ContentPlaceHolder1$allwords"></div>
	<div class="error-div"><span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_allwordsValidator">This search does not accept special characters.  Please try your search again by entering letters, numbers and punctuation up to 100 characters.</span></div>
	

</fieldset>
<fieldset class="group">
	<label for="exactwording">This exact wording or phrase</label>
	<div class="field"><input type="text" value="" class="text full" id="ctl00_ContentPlaceHolder1_exactwording" name="ctl00$ContentPlaceHolder1$exactwording"></div>
	<div class="error-div"><span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_exactwordingValidator">This search does not accept special characters.  Please try your search again by entering letters, numbers and punctuation up to 100 characters.</span></div>
	
	
</fieldset>
<fieldset class="group">
	<label for="oneormore">One or more of these words</label>
	<div class="field oneormore">
	<input type="text" value="" class="text" id="ctl00_ContentPlaceHolder1_oneormore1" name="ctl00$ContentPlaceHolder1$oneormore1"><em>OR</em>
	<input type="text" value="" class="text" id="ctl00_ContentPlaceHolder1_oneormore2" name="ctl00$ContentPlaceHolder1$oneormore2"><em>OR</em>
	<input type="text" value="" class="text" id="ctl00_ContentPlaceHolder1_oneormore3" name="ctl00$ContentPlaceHolder1$oneormore3">
	</div>
	<div class="error-div"><span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_oneormore1Validator">This search does not accept special characters.  Please try your search again by entering letters, numbers and punctuation up to 100 characters.</span></div>
	<div class="error-div"><span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_oneormore2Validator">This search does not accept special characters.  Please try your search again by entering letters, numbers and punctuation up to 100 characters.</span></div>
	<div class="error-div"><span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_oneormore3Validator">This search does not accept special characters.  Please try your search again by entering letters, numbers and punctuation up to 100 characters.</span>  
	</div>
	
		    
</fieldset>

<h3 class="topgap">But don't show pages that have...</h3>

<fieldset class="group">
	<label for="excludewords">Any of these unwanted words</label>
	<div class="field"><input type="text" value="" class="text full" id="ctl00_ContentPlaceHolder1_excludewords" name="ctl00$ContentPlaceHolder1$excludewords"></div>
	<div class="error-div"><span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_excludewordsValidator">This search does not accept special characters.  Please try your search again by entering letters, numbers and punctuation up to 100 characters.</span>
    </div>
</fieldset>

<h3 class="trigger"><a href="#">Additional Search Options</a></h3>
<div class="toggle_container" style="display: none;">
<div class="formcol">
<fieldset class="group  first">
	<label for="nh">Results per page</label>
	<div class="field">
	<select id="ctl00_ContentPlaceHolder1_nh" name="ctl00$ContentPlaceHolder1$nh">
		<option value="10" selected="selected">10 results</option>
		<option value="25">25 results</option>
		<option value="100">100 results</option>
		<option value="500">500 results</option>

	</select>
	<span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_nhValidator">You may only display up to 500 results.</span> 
	</div>
</fieldset>
<fieldset class="group">
	<label for="wherekeys">Keywords appear</label>
	<div class="field">
	<select id="ctl00_ContentPlaceHolder1_wherekeys" name="ctl00$ContentPlaceHolder1$wherekeys">
		<option value="">Anywhere in the page</option>
		<option value="allintitle:">In the title of the page</option>
		<option value="allinurl:">In the URL of the page</option>
		<option value="allinanchor:">In a link on the page</option>

	</select>
	
	
	</div>
</fieldset>
</div>

<div class="formcol">
<fieldset class="group first">
	<label for="inthe">Date</label>
	<div class="field">
		<select id="ctl00_ContentPlaceHolder1_inthe" name="ctl00$ContentPlaceHolder1$inthe">
		<option value="0">Anytime</option>
		<option value="Day">Past 24 hours</option>
		<option value="Week">Past week</option>
		<option value="Month">Past month</option>
		<option value="Year">Past year</option>

	</select>
	  
	</div>
</fieldset>
<fieldset class="group">
	<label for="filetype">File type</label>
	<div class="field">
		<select id="ctl00_ContentPlaceHolder1_filetype" name="ctl00$ContentPlaceHolder1$filetype">
		<option value="">Any format</option>
		<option value="html">Web Page</option>
		<option value="pdf">Adobe Acrobat PDF (.pdf)</option>
		<option value="xls">Microsoft Excel (.xls)</option>
		<option value="ppt">Microsoft Powerpoint (.ppt)</option>
		<option value="doc">Microsoft Word (.doc)</option>

	</select>
	
	</div>
</fieldset>
</div>

<div class="clear">&nbsp;</div>
</div><!-- close additional options -->
<div class="toggle_container" style="display: none;">
<div class="formcol">
<fieldset class="group  first">
	<label for="nh">Results per page</label>
	<div class="field">
	<select id="ctl00_ContentPlaceHolder1_nh" name="ctl00$ContentPlaceHolder1$nh">
		<option value="10" selected="selected">10 results</option>
		<option value="25">25 results</option>
		<option value="100">100 results</option>
		<option value="500">500 results</option>

	</select>
	<span style="color: Red; display: none;" class="error-red" id="ctl00_ContentPlaceHolder1_nhValidator">You may only display up to 500 results.</span> 
	</div>
</fieldset>
<fieldset class="group">
	<label for="wherekeys">Keywords appear</label>
	<div class="field">
	<select id="ctl00_ContentPlaceHolder1_wherekeys" name="ctl00$ContentPlaceHolder1$wherekeys">
		<option value="">Anywhere in the page</option>
		<option value="allintitle:">In the title of the page</option>
		<option value="allinurl:">In the URL of the page</option>
		<option value="allinanchor:">In a link on the page</option>

	</select>
	
	
	</div>
</fieldset>
</div>

<div class="formcol">
<fieldset class="group first">
	<label for="inthe">Date</label>
	<div class="field">
		<select id="ctl00_ContentPlaceHolder1_inthe" name="ctl00$ContentPlaceHolder1$inthe">
		<option value="0">Anytime</option>
		<option value="Day">Past 24 hours</option>
		<option value="Week">Past week</option>
		<option value="Month">Past month</option>
		<option value="Year">Past year</option>

	</select>
	  
	</div>
</fieldset>
<fieldset class="group">
	<label for="filetype">File type</label>
	<div class="field">
		<select id="ctl00_ContentPlaceHolder1_filetype" name="ctl00$ContentPlaceHolder1$filetype">
		<option value="">Any format</option>
		<option value="html">Web Page</option>
		<option value="pdf">Adobe Acrobat PDF (.pdf)</option>
		<option value="xls">Microsoft Excel (.xls)</option>
		<option value="ppt">Microsoft Powerpoint (.ppt)</option>
		<option value="doc">Microsoft Word (.doc)</option>

	</select>
	
	</div>
</fieldset>
</div>

<div class="clear">&nbsp;</div>
</div>
                                 
                                  
<div class="center topgap"><button type="submit">Advanced Search</button></div>
</div>





