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

include_once("../ob_config.php");
include("./includes/ob_vars.inc");

if($ok) {
	include("./tmpl/ob_header.inc");
	if ($action == "author") {
		include ("./forms/ob_addauthor.inc");
	} elseif ($action == "review") {
		include("./forms/ob_addreview.inc");
	} else {
		include("./forms/ob_login.inc");
	}
	include("./tmpl/ob_footer.inc");
} else {
	header("Location: login.php");;
}


?>
