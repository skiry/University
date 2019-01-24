<?php
    $servername = "localhost";
    $user = "root";
    $password = "";
    $dbname = "enterprise_system";

    $conn = new mysqli($servername, $user, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    $sql = "SELECT `Full Name`, `Role` FROM users";
    $queryResult = $conn->query($sql);
    
    $results = array();

    echo "<option value=\"\">Select an user</option>";

    while ($row = $queryResult->fetch_assoc()) {
        if ( ( stripos($row["Role"], $_GET['q']) === 0 || $_GET['q'] == "" )
                && !in_array($row["Full Name"], $results ) ) {
            array_push($results, $row["Full Name"]);
            echo "<option value=\"" . $row["Full Name"] . "\">" . $row["Full Name"] . "</option>";
        }
    }
?>