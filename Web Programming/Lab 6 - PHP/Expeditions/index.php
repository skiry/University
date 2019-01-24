<html>
    <head>
        <title>Welcome</title>
    </head>

    <body>
        <?php
        session_start();
        $_SESSION['planets'] = array();
        ?>
        
        <form action="show_planets.php" method="POST">
            Your name: <input type="text" name="name"><br>
            <input type="submit" value="Submit">
        </form>
    </body>
</html>