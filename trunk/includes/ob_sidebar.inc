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

/*=====================================================================
 * sidebar function(s)
 *
 * For now, there is only one, but there may be more in the future.
 * Always hard to tell. This function displays the months in the
 * year and adds hyperlinks to those months that have already occurred
 * or that we are in currently.
 *=====================================================================
**/

function printmonths() {
   global $startyear;
   global $thisyear;
   global $thisfile;

   if($thisyear > $startyear) {
     for(($x = $thisyear - $startyear); $x >= 0; $x--) {
       $yr = $startyear + $x;
       echo "<h1>{ <a href=\"$thisfile/date/$yr\">$yr</a> }</h1>\n\n<p>";
       loopmonths(($startyear + $x));
       echo "</p>\n\n";
     }
   } elseif ($thisyear == $startyear) {
     echo "<h1>{ this year }</h1></h1>\n\n<p>";
     loopmonths($thisyear);
     echo "</p>\n\n";
   }
}

function loopmonths($whichyear) {
   global $months;
   global $thisfile;
   global $thismonth;
   global $thisyear;

   $quarter = 0;
   $uptonow = true;

    echo "<table border=\"0\" width=\"125\" cellspacing=\"0\" cellpadding=\"0\">";

   if($whichyear == $thisyear) {
    for($x = 0;$x < count($months); $x++) {
        if($quarter == 0) {
            echo "<tr>";
        }
        $quarter++;
        $mon = substr($months[$x],0,3);
        if ($uptonow == true) {
            echo "<td><a href=\"$thisfile/date/$thisyear/$months[$x]\">$mon</a></td>";
            if($months[$x] == $thismonth) {
                $uptonow = false;
            }
        } else {
            echo "<td>$mon</td>";
        }
        if ($quarter == 4) {
            echo "</tr>\n";
            $quarter = 0;
        }
    }
   } elseif($whichyear < $thisyear) {
        for($x = 0; $x < count($months); $x++) {
            $mon = substr($months[$x],0,3); 
            if ($quarter == 0) {
                echo "<tr>";
            }
            $quarter++;
            print "<td><a href=\"$thisfile/date/$whichyear/$months[$x]\">";
            print "$mon</a></td>";
            if($quarter == 4) {
                echo "</tr>\n";
                $quarter = 0;
            } 
        }
    }
    echo "</table>\n";
}
?>
