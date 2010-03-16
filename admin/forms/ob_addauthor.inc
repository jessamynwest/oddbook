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
?>
<form method="post" action="<?= $actfile ?>">

	<input type="hidden" name="action" value="insert">
	<input type="hidden" name="what" value="author">

	<h2><a name="a_rev"></a>Add an Author</h2>

	<span class="formtext">Last Name</span><br>

	<input name="lname" type="text" size="35" class="forminput">

	<br><br>

	<span class="formtext">First Name</span><br>

	<input name="fname" size="35" class="forminput"><br><br>
	<input type="submit" value="do it." class="button">

</form>
