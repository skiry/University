<?php
    $servername = "localhost";
    $user = "root";
    $password = "";
    $dbname = "enterprise_system";

    $mysqli = new mysqli($servername, $user, $password, $dbname);
    if($mysqli->connect_error) {
        die("Connection failed: " . $mysqli->connect_error);
    }

    $sql = "SELECT `Full Name`, `Username`, `Age`, `Role`, `Email`, `Webpage`
    FROM users WHERE `Full Name`=?";

    $stmt = $mysqli->prepare($sql);
    $stmt->bind_param("s", $_GET['q']);
    $stmt->execute();
    $stmt->store_result();
    $stmt->bind_result($fullname, $username, $age, $role, $email, $webpage);
    $stmt->fetch();
    $stmt->close();

    if ($fullname) {
        echo "<table>";
        echo "<tr><th>Full Name</th>";
        echo "<td>" . $fullname . "</td></tr>";
        echo "<tr><th>Username</th>";
        echo "<td>" . $username . "</td></tr>";
        echo "<tr><th>Age</th>";
        echo "<td>" . $age . "</td></tr>";
        echo "<tr><th>Role</th>";
        echo "<td>" . $role . "</td></tr>";
        echo "<tr><th>Email</th>";
        echo "<td>" . $email . "</td></tr>";
        echo "<tr><th>Webpage</th>";
        echo "<td>" . $webpage . "</td></tr>";
        echo "</table>";

        if (isset($_GET['d'])) {
            echo '<input type="submit" value="Delete User">';
        }
    }
?> 