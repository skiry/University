<?php 
session_start();

    echo "Successful conference reservations: ";
    for($i = 0 ; $i < count($_SESSION["successes"]) ; $i++) {
     echo $_SESSION['successes'][$i] . "<br/>";
    }  

    echo "Failed conference reservations: ";
    for($i = 0 ; $i < count($_SESSION["failures"]) ; $i++) {
     echo $_SESSION['failures'][$i] . "<br/>";
    }  
?>