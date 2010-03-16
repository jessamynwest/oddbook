<?php
function display() {
     global $desc_array;

     $this_str = $desc_array[func_get_arg(0)];
     $to_return = func_get_arg(1);
     $this_array = split("\|",$this_str);

     echo $this_array[$to_return];
     
}


function nav() {
     global $desc_array,$indexfile;
     $direct = func_get_arg(0);
     $loc = func_get_arg(1);
     $this_file = getenv("SCRIPT_NAME");
     $next = $loc + 1;
     $prev = $loc - 1;
     if ($direct == 'back') {
          if ($loc == 1) {
               print $indexfile;
          } else {
               print "$this_file?x=$prev";
          }
     }
     elseif ($direct == 'forward') {
          if ($loc == (count($desc_array) - 1)) {
               print $indexfile;
          } else {
               print "$this_file?x=$next";
          }
     }
}

//define variables
$desc_file = 'photo.desc';
$desc_array = file($desc_file); 
$globals_str = $desc_array[0];

$global_stuff = split("\|",$globals_str);
$title = $global_stuff[0];
$indexfile = $global_stuff[1];

//do an integer check on the querystring.
//default value of 1.
//kind of a hack job here, because I can't
//get querystring values to be recognized
//as integers.

if(is_numeric($_REQUEST['x'])) {
    if (($_REQUEST['x'] > 0) && ($_REQUEST['x'] < count($desc_array))) {
          $which = floor($_REQUEST['x']);
     } else {
          $which = 1;
     }

} else {
     $which = 1;
}

//get the global variables from the config file.
?>
