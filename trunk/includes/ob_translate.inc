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
 * translation functions
 *
 * This function translates quotes into ascii entities using the 
 * preg_replace() php function.
 * ====================================================================
 **/

function translate() {
  $input = stripslashes(func_get_arg(0));
  $thestring = strtr($input, "\n"," ");
    /* here are a list of the patterns in the array:
     * 0. double quotes
     * 1. single quotes for possessives and contractions.
     * 2. single quotes for quotes within quotes.
     * */

    $patterns = array("/(.*?[ >])\"(.*?)\"([\s<])/",
                      "/([a-zA-Z0-9])\'([a-zA-Z])/",
                      "/(.*?[ >])'(.*?)'([\s<]|&#8221)/");
    $replacements = array("$1&#8220;$2&#8221;$3",
                          "$1&#8217;$2",
                          "$1&#8216;$2&#8217;$3");
    return preg_replace($patterns,$replacements,$thestring);
}

function render_review($result, $grabcats=true){
	global $thisfile, $logged_in;

	// Grab book category links
	if ( $grabcats ) {
		$cat_label = 'category';
		$cats = dn_select_cat_by_book( $result['review_id'] );
		if ( count($cats) == 1 ) {
			$cat_value = $cats[0];
		} elseif ( count($cats) == 0 ) {
			$cat_value = 'uncategorized';
		} else {
			$cat_label = 'categories';
			$cat_value = implode( ', ', $cats );
		}
	} else {
		$cat_label = '';
		$cat_value = '';
	}

	$title = translate($result['title']);

	if (strlen($result['isbn']) >= 10 && strlen($result['isbn']) <= 13) {
		$isbn = "<a href=\"http://www.powells.com/cgi-bin/partner?partner_id=27086&cgi=product&isbn=". $result['isbn'] ."\" title=\"buy ". $result['sw'] ." $title from powells\"><img src=\"http://jessamyn.info/pix/buy.png\" border=\"0\" width=\"10\" height=\"13\"></a>";
	} else {
		$isbn = "";
	} 
	
	if ( $logged_in ) {
		$isbn .= "&nbsp;<small>[<a href='/admin/edit.php?action=review&id=".$result['review_id']."'>edit</a>]</small>";
	}

	#echo strlen($result['isbn']);

	//first, get translation out of the way.
	$trans_elements = array($title,
					translate($result['auth_f']),
					translate($result['auth_l']),
					translate($result['text']),
					$isbn
	);

	//now set up two arrays that will replace the elements
	$review_elements = array("/##sw##/",
					"/##title##/",
					"/##link##/",
					"/##author##/",
					"/##pub_date##/",
					"/##read_date##/",
					"/##cat_label##/",
					"/##cat_value##/",
					"/##rating##/",
					"/##text##/",
					"/##storelink##/"
	);

	$review_replace = array($result['sw'],
					$trans_elements[0],
					"$thisfile/book/" . $result['review_id'],
					$trans_elements[1] . " " . $trans_elements[2],
					$result['pubyear'],
					$result['review_day'] . " " . $result['review_month'] . " " . $result['review_year'],
					$cat_label,
					$cat_value,
					$result['rating'],
					$trans_elements[3],
					$isbn
	);
	
	$fp = array_pop($result);
	while(!feof($fp)) {
		echo preg_replace($review_elements,$review_replace,fgets($fp,1024));
	}
	rewind($fp);
}

?>
