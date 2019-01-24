<html>
    <head>
        <title>Deleting an user...</title>
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
                xhttp.open("GET", "liveSearchName.php?d=1&q="+document.getElementById("nameInput").value, true);
                xhttp.send();
            }
        </script>
    </head>

    <body>
        <header>
            <h1 class="banner">Enterprise System</h1>
        </header>

        <?php 
        $fullname = "";
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            $fullname = parseInput($_POST["fullname"]);
        }

        function parseInput($input) {
            $input = trim($input);
            $input = stripslashes($input);
            $input = htmlspecialchars($input);

            return $input;
        }
        ?>

        <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
                <label>Full name to delete</label>
                <input type="text" id="nameInput" name="fullname"><br/>
            <div id="newUserInfo"></div>
            <button type="button" style="" onclick="showInfo()">Search User</button>
        </form>

        <?php
            $servername = "localhost";
            $user = "root";
            $password = "";
            $dbname = "enterprise_system";

            $conn = new mysqli($servername, $user, $password, $dbname);
            
            if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
            } 
            
            $sql = $conn->prepare("SELECT * FROM users WHERE `Full Name`=?");
            $sql->bind_param("s", $fullname);
            $sql->execute();
           
            if (!$sql->fetch()) {
                echo "<span class=\"error\">User does not exist!</span>";
            }
            else {
                $sql->close();
                $stmt = $conn->prepare("DELETE FROM users WHERE `Full Name`=?");
                $stmt->bind_param("s", $fullname);
                $stmt->execute();


                echo '<script type="text/javascript">alert("User successfully deleted!");</script>';
            }
            

            $conn->close();
        ?>
    </body>
</html>