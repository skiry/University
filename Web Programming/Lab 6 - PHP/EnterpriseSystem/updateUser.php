<html>
    <head>
        <title>Updating an user...</title>
        <link rel="stylesheet" type="text/css" href="style.css">
        <script>
            function showInfo() {
                var xhttp;
                if (document.getElementById("nameInput").value == "") {
                    document.getElementById("newUserInfo").innerHTML = "";
                    return;
                }
                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("newUserInfo").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "lastUserInfo.php?q="+document.getElementById("nameInput").value, true);
                xhttp.send();
            }
        </script>
    </head>

    <body>
        <header>
            <h1 class="banner">Enterprise System</h1>
        </header>

        <?php 
        $fullname = $username = $role = $email = $webpage = $password = "";
        $age = $ok = 0;
        $inputData = array("fullname", "username", "password", "age", "role", "email", "webpage", "oldUsername");
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            foreach ($inputData as $current) {
                if (!empty($_POST[$current])) { 
                    $ok = $ok + 1;
                    ${$current} = parseInput($_POST[$current]);
                }
            }
        }

        function parseInput($input) {
            $input = trim($input);
            $input = stripslashes($input);
            $input = htmlspecialchars($input);

            return $input;
        }
        ?>

        <form method="post" action="<?php echo $_SERVER['PHP_SELF']; ?>">
                <label>Current Username</label>
                <input type="text" id="nameInput" name="oldUsername"><br/>
            <div id="newUserInfo"></div>
            <button type="button" style="" onclick="showInfo()">Search User</button>
        </form>

        <?php
            if ($ok != 8) {
                echo "<span class=\"error\">*Please fill in all fields!</span>";
            }
            else {
                $servername = "localhost";
                $user = "root";
                $password = "";
                $dbname = "enterprise_system";

                $conn = new mysqli($servername, $user, $password, $dbname);
                
                if ($conn->connect_error) {
                    die("Connection failed: " . $conn->connect_error);
                } 

                $stmt = $conn->prepare("UPDATE users SET `Full Name`=?, `Username`=?, `Password`=?, `Age`=?, `Role`=?, `Email`=?, `Webpage`=? 
                WHERE `Username`=?");
                $encrypted_pass = sha1($password);
                $stmt->bind_param("sssissss", $fullname, $username, $encrypted_pass, $age, $role, $email, $webpage, $oldUsername);
                $stmt->execute();

                echo '<script type="text/javascript">alert("User informations successfully updated!");</script>';
                
                $conn->close();
            }
        ?>
    </body>
</html>