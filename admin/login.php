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

if( $ok ) {
	if ( $_GET['action'] == 'logout' ) {
		dn_end_session( $_COOKIE['obSessID'] );
		header("Location: /booklist");
		exit;
	}
	echo "$ok | Logged in. | <a href='login.php?action=logout'>logout</a>";
	exit;
}

/*
 * Validate input
<input type="hidden" name="action" value="login">
<input name="username" type="text" size="35" class="forminput"><br><br>
<input name="password" type="password" size="35" class="forminput">
<input type="submit" value="login." class="button">
 */
$user = $_POST['username'];
$pw = $_POST['password'];

$user = mysql_escape_string( $user );
$pw = mysql_escape_string( $pw );

$validLogin = dn_validate_login( $user, $pw );
if ( $validLogin ) {
	dn_begin_session( $user );
	
	
	/* echo "<pre>\n";
	$sessID = $user;
	$sessFile = "/f5/cowbellemoo/home/protected/cowbellemoo";
	$currTime = time();
	if ( (is_writable($sessFile)) || (is_writable(SESS_DIR) && !file_exists($sessFile)) ) {
		if ( !$handle = fopen($sessFile, 'w') ) {
			echo "failed to open file for writing\n";
		}
		if ( fwrite($handle, $currTime) === FALSE ) {
			echo "failed to write to file\n";
		}
		fclose( $handle );
	} else {
		echo "failed to determinine writability or existance of file\n";
	}
	
	echo "file writable: " . is_writable($sessFile) . "\n";
	echo "folder writable: " . is_writable(SESS_DIR) . "\n";
	echo "file exists: " . file_exists($sessFile) . "\n";
	*/
	
	/* 
	echo "<pre>\n";
	echo "Username: " . $user . "\n";
	echo "Password: " . $pw . "\n";
	echo "</pre>\n";	
	*/
	
	header("Location: index.php");
}


include("./tmpl/ob_header.inc");

$actfile = './login.php';
include("./forms/ob_login.inc");

include("./tmpl/ob_footer.inc");
?>
