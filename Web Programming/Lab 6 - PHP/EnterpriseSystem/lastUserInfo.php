<?php
    $servername = "localhost";
    $user = "root";
    $password = "";
    $dbname = "enterprise_system";

    $conn = new mysqli($servername, $user, $password, $dbname);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 

    $sql = $conn->prepare("SELECT * FROM users WHERE Username=?");
    $sql->bind_param("s", $_GET['q']);
    $sql->execute();
    $sql->bind_result($fullname, $username, $encrypted_pass, $age, $role, $email, $webpage);
    if ($sql->fetch()) {
        echo '
        <br/>
        <br/>
        <p>
            <label>New Full name</label> 
            <input type="text" name="fullname" value="' . $fullname .  '"><br/>
        </p>
        <p>
            <label>New Username</label> 
            <input type="text" name="username" value="' . $username .  '"><br/>
        </p>
        <p>
            <label>New Password</label> 
            <input type="password" name="password"><br/>
        </p>
        <p> 
            <label>New Age</label> 
            <input type="number" name="age" value="' . $age .  '"><br/>
        </p>
        <p>
            <label>New Role</label> 
            <input type="text" name="role" value="' . $role .  '"><br/>
        </p>
        <p>
            <label>New Email</label> 
            <input type="email" name="email" value="' . $email .  '"><br/>
        </p>
        <p>
            <label>New Webpage</label> 
            <input type="text" name="webpage" value="' . $webpage .  '"><br/>
        </p>
        <input type="submit" value="Update User Info">';
    }
    else {
        echo "<span class=\"error\">User not found!</span>";
    }

    $conn->close();
?>