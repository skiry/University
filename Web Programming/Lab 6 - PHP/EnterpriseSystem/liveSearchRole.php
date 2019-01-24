<?php
    $servername = "localhost";
    $user = "root";
    $password = "";
    $dbname = "enterprise_system";

    $mysqli = new mysqli($servername, $user, $password, $dbname);
    if($mysqli->connect_error) {
        die("Connection failed: " . $mysqli->connect_error);
    }

    $sql = "SELECT `Role` FROM users";
    $result = $mysqli->query($sql);
    
    $hint = "";
    $freq = array();
    $putBr = 0;

    while ($row = $result->fetch_assoc()) {
        if (stripos($row["Role"], $_GET['q']) === 0 && !in_array($row["Role"], $freq)) {
            if ($putBr) {
                $hint = $hint . "<br/>";
            }
            $hint = $hint . $row["Role"];
            array_push($freq, $row["Role"]);
            $putBr = 1;
        }
    }

    if ($hint=="") {
        $response="No suggestion";
    } 
    else {
        $response=$hint;
    }

    echo $response;
?> 