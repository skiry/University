<html>
    <head>
        <title>Adding an user...</title>
        <link rel="stylesheet" type="text/css" href="style.css">
    </head>

    <body>
        <header>
            <h1 class="banner">Enterprise System</h1>
        </header>

        <?php 
        $fullname = $username = $role = $email = $webpage = $password = "";
        $age = $ok = 0;
        $inputData = array("fullname", "username", "password", "age", "role", "email", "webpage");
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

        <form method="post" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]);?>">
            <p>
                <label>Full name</label> 
                <input type="text" name="fullname"><br/>
            </p>
            <p>
                <label>Username</label> 
                <input type="text" name="username"><br/>
            </p>
            <p>
                <label>Password</label> 
                <input type="password" name="password"><br/>
            </p>
            <p> 
                <label>Age</label> 
                <input type="number" name="age"><br/>
            </p>
            <p>
                <label>Role</label> 
                <input type="text" name="role"><br/>
            </p>
            <p>
                <label>Email</label> 
                <input type="email" name="email"><br/>
            </p>
            <p>
                <label>Webpage</label> 
                <input type="text" name="webpage"><br/>
            </p>
            <input type="submit" value="Add User">
        </form>

        <?php
            if ($ok != 7) {
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

                $sql = $conn->prepare("SELECT * FROM users WHERE Username=?");
                $sql->bind_param("s", $username);
                $sql->execute();
                if ($sql->fetch()) {
                    echo "<span class=\"error\">User already exists!</span>";
                }
                else {
                    $stmt = $conn->prepare("INSERT INTO users (`Full Name`, `Username`, `Password`, `Age`, `Role`, `Email`, `Webpage`)
                    VALUES (?, ?, ?, ?, ?, ?, ?)");
                    $encrypted_pass = sha1($password);
                    $stmt->bind_param("sssisss", $fullname, $username, $encrypted_pass, $age, $role, $email, $webpage);
                    $stmt->execute();

                    echo "<span class=\"success\">User successfully added!</span>";
                }

                $conn->close();
            }
        ?>
    </body>
</html>