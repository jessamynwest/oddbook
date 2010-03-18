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

//non-customized variables we'll need throughout the application.
$thisfile = getenv("SCRIPT_NAME");
$pathstr = getenv("PATH_INFO");
$date = getdate();
$thisyear = $date['year'];
$thismonth = strtolower($date['month']);
$months = array( 'january',
                 'february',
                 'march',
                 'april',
                 'may',
                 'june',
                 'july',
                 'august',
                 'september',
                 'october',
                 'november',
                 'december'
                );

//this function returns the current date.
function datepart() {
     $whichpart = func_get_arg(0);
     $thedate = getdate();

     if($whichpart == 'month') {
          return strtolower($thedate[$whichpart]);
     } else {
          return $thedate[$whichpart];
     }
}
?>
