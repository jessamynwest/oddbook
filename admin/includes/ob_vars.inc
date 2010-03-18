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

/* ====================================================================
 * This file contains global variables. 
 * ====================================================================
**/

/*
 * -------------------------------------------------------------------- 
 * Database information. 
 * 
 * Fill in the variables with the values specific to
 * your system below.
 *
**/

// User/Site Settings


//other files to link to...
$index = "index.php";
$actfile = "act.php";
$addfile = "add.php";
$editfile = "edit.php";

//cookies...
include_once("../includes/ob_vars.inc");
include_once("../includes/ob_cats.inc");
dn_db_connect();

$ok = $_COOKIE['reviewer'];
$ok = dn_validate_session();

//and request method.
$action = $_GET['action'];
?>
