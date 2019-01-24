<html>
    <head>
        <title>Welcome</title>
        <link rel="stylesheet" type="text/css" href="style.css">
    </head>

    <body>
        <?php
        session_start();
        $_SESSION["successes"] = array();
        $_SESSION["failures"] = array();
        ?>
        
        <form action="reserve_flight.php" method="POST">
            Your name: <input type="text" name="name"><br>
            <input type="submit" value="Submit">
        </form>
    </body>
</html>