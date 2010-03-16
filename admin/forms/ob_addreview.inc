<?php
/*
 * This file is part of Oddbook.
 *
 * Oddbook is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 * 
 * Oddbook is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with Oddbook; if not, write to the Free Software Foundation, Inc.,  59
 * Temple Place, Suite 330, Boston, MA  02111-1307  USA
**/

include("./includes/ob_lib.inc");

/*
 * this function is for the date.
 *
 **/

function read_date($datepart) {
	$today = getdate();
	$months = array (
		   'January',
		   'February',
		   'March',
		   'April',
		   'May',
		   'June',
		   'July',
		   'August',
		   'September',
		   'October',
		   'November',
		   'December'
		   );
		   
	switch($datepart) {
		case 'month':
			for($count = 0;$count <= 11;$count++) {
				if($today['mon'] == ($count + 1)) {
					print "<option selected value=\"".($count+1)."\">".$months[$count]."</option>\n";
				} else {
					print "<option value=\"".($count+1)."\">".$months[$count]."</option>\n";
				}
			}
			break;
		case 'day':
			for($count = 1;$count <= 31;$count++) {
				if($today['mday'] == ($count)) {
					print "<option selected value=\"".($count)."\">".($count)."</option>\n";
				} else {
					print "<option value=\"".($count)."\">".($count)."</option>\n";
				}
			}
			break;
	}
}

?>

<form method="post" action="<?= $actfile ?>">

	<input type="hidden" name="action" value="insert">
	<input type="hidden" name="what" value="review">

	<h2><a name="a_rev"></a>Add a Review</h2>

	<p><span class="formtext">Author Name (<a href="javascript:popener('<?= $addfile ?>?action=author','addAuth');">add an author</a>)</span>
	<br>
	<select class="forminput" name="authID">
	<? get_authors(); ?>
	</select>

	<br><br>
	<span class="formtext">Title</span><br>

	<input name="title" type="text" size="100" class="forminput">

	<br><br>

	<span class="formtext">Publication Year</span><br>

	<input name="year" type="text" size="35" class="forminput">

	<br><br>
	<span class="formtext">ISBN</span><br>

	<input name="ISBN" type="text" size="35" class="forminput">

	<br><br>

	<span class="formtext">Category:</span>
	<select class="forminput" name="cid-1">
	<option value="0" selected>-</option>
	<? get_cats(); ?>
	</select>
	<select class="forminput" name="cid-2">
	<option value="0" selected>-</option>
	<? get_cats(); ?>
	</select>
	&nbsp;&nbsp;&nbsp;
	<span class="formtext">Rating: </span>
	<select name="rating" class="forminput">
	<?php
	$ratings = array('+','0','-');
	foreach($ratings as $rating){
	  echo "<option value=\"$rating\">$rating</option>\n";
	}
	?>
	</select>

	<br>
	<textarea name="review_text" rows="12" cols="60" 
	class="forminput"></textarea>
	<br><br>

	<span class="formtext">Date Read</span><br>
	<select name="read_month" class="forminput">
	<?php 
	read_date('month'); 
	?>
	</select>&nbsp;&nbsp;
	<select name="read_day" class="forminput">
	<?php 
	read_date('day') 
	?>
	</select>&nbsp;&nbsp;
	<input name="read_year" type="text" size="4" class="forminput" value="<?= date('Y') ?>">
	<br>
	<input type="submit" value="do it." class="button">

</form>
