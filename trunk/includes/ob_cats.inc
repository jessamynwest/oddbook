<?php
/**
 FILE: ob_dano.inc
 * Supplementary functions for Oddbook by dano.
 *
 * @package oddbook
 *
 * @history _
 * <br>$Log$
 * 
 * @license See comment in source.
 * @version $Id$
 * @author Dano <qorg.org@gmail.com>
 *
*/

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

#
# BEGIN TEMPLATE FUNCTIONS
#

/**
 FUNCTION: dn_link_template()
 * Returns a link.
 *
 * Called by: dn_select_by_cat().
 *
 * @param string $url URL for link.
 * @param string label URL for link.
 * @return string html link.
 */
function dn_link_template( $url, $label ) {
	return "<a href='$url'>$label</a> ";
}

/**
 FUNCTION: dn_pipebeforelink_template()
 * Returns a link with a small gray pipe char before it.
 *
 * Called by: dn_printcats().
 *
 * @param string $url URL for link.
 * @param string label URL for link.
 * @return string html link.
 */
function dn_pipebeforelink_template( $url, $label ) {
	return "<small style='color:gray;'>|</small>&nbsp;".dn_link_template($url, $label)." \n";
}

#
# END TEMPLATE FUNCTIONS
# BEGIN OUTPUT FUNCTIONS
#

/**
 FUNCTION: dn_printcats()
 * Outputs a list of category names as links.
 *
 * Retrieves, formats and displays category names.
 * Uses template: dn_pipebefore_template().
 *
 * @param none.
 * @return void.
 */
function dn_printcats() {
	global $thisfile;
	dn_db_connect();

	echo dn_pipebeforelink_template( "$thisfile/cat", 'all categories' );
	
	$cat_names = dn_cat_names();
	if ( !is_array($cat_names) ) {
		$cat_names = array( 'err' => 'Category error' );
	}
	foreach ( $cat_names as $cat => $name ) {
		$url = "$thisfile/cat/".urlencode($name);
		$name = str_replace( ' ', '&nbsp;', $name );
		echo dn_pipebeforelink_template( $url, $name );
	}
	return;
}

/**
 FUNCTION: dn_select_by_cat()
 * O.
 *
 * R.
 * Uses template: dn_ _template().
 *
 * @param none.
 * @return void.
 */
function dn_select_by_cat( $mycat='' ) {
	global $thisfile;

	$cat_names = dn_cat_names( urldecode($mycat) );
	if ( !is_array($cat_names) ) {
		$cat_names = array( 'err' => 'Category error' );
	}
	foreach ( $cat_names as $cat => $name ) {
		$titles = dn_cat_bookdata($cat);
		#echo "<pre>".print_r($titles,true)."</pre>";
		
		echo "<h1>$name</h1>\n<p>\n";
		if ( is_array($titles) && count($titles) ) {
			foreach ( $titles as $id => $title ) {
				$url = "$thisfile/book/".$id;
				echo dn_link_template($url, $title)."<br />\n";
			}
		} else {
				echo "<em>No titles found.</em>\n";
		}
		echo "</p>\n";
	}
	return;
}

/**
 FUNCTION: dn_select_cat_by_book()
 * O.
 *
 * R.
 * Uses template: dn_ _template().
 *
 * @param none.
 * @return void.
 */
function dn_select_cat_by_book( $review_id, $link=true ) {
	global $thisfile;
	$cat_names = dn_cat_by_book($review_id);
	if ( !is_array($cat_names) ) {
		$cat_names = array( 'error' );
	}
	foreach ( $cat_names as $cat => $name ) {
		if ( $link ) {
			$url = "$thisfile/cat/".urlencode($name);
			$rtn[] = trim(dn_link_template($url, $name));
		} else {
			$rtn[] = trim( $name );
		}
	}
	return $rtn;
}

#
# END OUTPUT FUNCTIONS
# BEGIN BUSINESS FUNCTIONS
#

/**
 FUNCTION: dn_cat_bookdata()
 * R.
 *
 * Requires open DB connection.
 *
 * @param none.
 * @return array.
 */
function dn_cat_bookdata($cat) {
	$rtn = array();
	$sql = "SELECT r.review_id AS id, b.title_sw, TRIM(b.title) AS title
		FROM category AS c, review as r, book AS b, cat_book_link AS cb
		WHERE c.cat_id = $cat
		AND c.cat_id = cb.cat_id
		AND r.book_id = b.book_id
		AND b.book_id = cb.book_id
		ORDER BY title ASC";
	$result = mysql_query($sql);
	while ($row = @mysql_fetch_assoc($result)) {
		$id = $row['id'];
		$rtn[$id] = $row['title_sw'].' '.$row['title'];
	}
	return $rtn;
}

/**
 FUNCTION: dn_cat_by_book()
 * R.
 *
 * Requires open DB connection.
 *
 * @param none.
 * @return array.
 */
function dn_cat_by_book($review_id) {
	$rtn = array();
	$sql = "SELECT TRIM(c.cat_name) AS cat_name
		FROM category AS c, review as r, book AS b, cat_book_link AS cb
		WHERE r.review_id = $review_id
		AND c.cat_id = cb.cat_id
		AND r.book_id = b.book_id
		AND b.book_id = cb.book_id
		ORDER BY cat_name ASC";
	$result = mysql_query($sql);
	while ($row = @mysql_fetch_assoc($result)) {
		$rtn[] = $row['cat_name'];
	}
	return $rtn;
}

/**
 FUNCTION: dn_cat_names()
 * Retrieves an array of category IDs and names.
 *
 * IDs are keys, names are values. Requires open DB connection.
 *
 * @param none.
 * @return array.
 */
function dn_cat_names( $cat='' ) {
	$rtn = array();
	$sql = "SELECT cat_id, cat_name FROM category ";
	if ( !empty($cat) ) {
		if ( is_numeric($cat) ) {
			$sql .= "WHERE cat_id='$cat' ";
		} else {
			$sql .= "WHERE cat_name='$cat' ";
		}
	}
	$sql .= "ORDER BY cat_name";
	$result = mysql_query($sql);
	while ($row = @mysql_fetch_assoc($result)) {
		$id = $row['cat_id'];
		$rtn[$id] = $row['cat_name'];
	}
	return $rtn;
}

/**
 FUNCTION: dn_db_connect()
 * Connect to database.
 *
 * Returns a database connection handle.  Requires db global vars.
 *
 * @param none.
 * @return string mysql conection handle.
 */
function dn_db_connect() {
	global $dbhost,$dbuser,$dbpass,$dbname;
	$conn = mysql_connect($dbhost,$dbuser,$dbpass);
	mysql_select_db($dbname);
	return $conn;
}

/**
 FUNCTION: dn_validate_login()
 * Validates login credentials.
 *
 * Returns ...
 *
 * @param none.
 * @return boolean true if userID and password are valid, or false
 */
function dn_validate_login( $user, $pw ) {
  $sql = "SELECT username FROM users 
          WHERE username = '$user' 
          AND password = PASSWORD('$pw');";
  $result = mysql_query($sql);
  $numrows = mysql_num_rows($result);
  mysql_free_result($result);

  if ( $numrows == 1 ) {
	  #phpinfo();
	  return true;
  }
  return false;
}

/**
 FUNCTION: dn_refresh_session()
 * Creates or updates user session.
 *
 * Returns ...
 *
 * @param none.
 * @return boolean true if userID and password are valid, or false
 */
function dn_hash_session( $sessID, $str='' ) {
	return md5( $sessID.SESS_CONSTANT.$str );
}
function dn_refresh_session( $sessID ) {
  $currTime = time();
  $hash = dn_hash_session( $sessID, $currTime );
  $sessFile = SESS_DIR.$sessID;


/* Removing for the moment

  # Write $currTime to a file named $sessID.
  if ( (is_writable($sessFile)) || (is_writable(SESS_DIR) && !file_exists($sessFile)) ) {
	if ( !$handle = fopen($sessFile, 'w') ) {
		return false;
	}
	if ( fwrite($handle, $currTime) === FALSE ) {
		return false;
	}
	fclose( $handle );
  } else {
	return false;
  }
  
*/

  # Set cookie obSessKey to $hash.
  setcookie( 'obSessKey', $hash, 0, '/' );

  return $hash;
}

/**
 FUNCTION: dn_create_session()
 * Creates or updates user session.
 *
 * Returns ...
 *
 * @param none.
 * @return boolean true if userID and password are valid, or false
 */
function dn_begin_session( $sessID='' ) {
  if ( empty($sessID) ) {
	  $sessID = $_SERVER['UNIQUE_ID'];
  }
  # Set cookie obSessID to $sessID.
  setcookie( 'obSessID', $sessID, 0, '/' );
  dn_refresh_session( $sessID );
  return true;
}

/**
 FUNCTION: dn_create_session()
 * Creates or updates user session.
 *
 * Returns ...
 *
 * @param none.
 * @return boolean true if userID and password are valid, or false
 */
function dn_end_session( $sessID ) {
	if ( empty($sessID) ) {
		return false;
	}
	if ( !@unlink( SESS_DIR.$sessID ) ) {
		return false;
	}

	if ( !setcookie( 'obSessID', '', 0, '/' ) ) {
		return false;
	}
	if ( !setcookie( 'obSessKey', '', 0, '/' ) ) {
		return false;
	}
	return true;
}

/**
 FUNCTION: dn_create_session()
 * Creates or updates user session.
 *
 * Returns ...
 *
 * @param none.
 * @return boolean true if userID and password are valid, or false
 */
function dn_validate_session() {
	$id = $_COOKIE['obSessID'];
	if ( empty($id) ) {
		return false;
	};

	$key = $_COOKIE['obSessKey'];
	if ( strlen($key) != 32 ) {
		return false;
	}


/*	Disabled until I figure out how the PHP file commands work with shared hosting

	$sessContent = @file_get_contents( SESS_DIR.$id );
	if ( $key != dn_hash_session($id, $sessContent) ) {
		return false;
	}
*/

	dn_refresh_session( $id );
	return true;
}

define( 'SESS_CONSTANT', 'afeb38961f4bff9808f6b978d2ed627b' );
define( 'SESS_DIR', '/f5/cowbellemoo/home/protected/' );

?>
