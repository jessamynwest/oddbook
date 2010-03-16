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

include("./includes/ob_vars.inc");
include("./includes/ob_actions.inc");

ob_start();

if($ok) {
	if ($_GET['action'] == 'delete') {
		if($_GET['what'] == 'author') {
			delete_author($_GET['id']);
		} elseif($_GET['what'] == 'review') {
			delete_review($_GET);
		}
	} elseif($_GET['action'] == 'dbstop') {
		update_db();
	} elseif(isset($_POST['action'])) {
		switch($_POST['action']) {
			case 'update':
				if ($_POST['what'] == 'author') {
					update_author($_POST);
				} elseif($_POST['what'] == 'review') {
					update_review($_POST);
				}
				break;
			case 'insert':
				if ($_POST['what'] == 'author') {
					insert_author($_POST);
				} elseif($_POST['what'] == 'review') {
					insert_review($_POST);
				}
				break;
		}
	}
} else {
	if($_POST['action'] == 'login') {
		login($_POST);
	} else {
		include("./forms/ob_login.inc");
	}
}

ob_end_flush();
include("./tmpl/ob_footer.inc");
?>
