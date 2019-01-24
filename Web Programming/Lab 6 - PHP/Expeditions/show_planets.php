<html>
    <head>
        <title>Show planets</title>
        <style>
            .dot {
                height: 25px;
                width: 25px;
                border-radius: 50%;
                display: inline-block;
            }
        </style>
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script>
            $(document).ready(function() {
                otherPlanets();
            });
            
            function otherPlanets() {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("planets").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "randomPlanets.php", true);
                xhttp.send();
            }

            function showInfo(el) {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("info").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "showStats.php?id=" + el.value, true);
                xhttp.send();
            }

            function empty(el) {
                document.getElementById("info").innerHTML = "";
            }

            function addExpedition(el) {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("info").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "addExpedition.php?id=" + el.value, true);
                xhttp.send();
            }
            
        </script>
    </head>

    <?php
    session_start();

     if ($_SERVER["REQUEST_METHOD"] == "POST") {
         $_SESSION["name"] = parseInput($_POST["name"]);
     }

     function parseInput($input) {
        $input = trim($input);
        $input = stripslashes($input);
        $input = htmlspecialchars($input);

        return $input;
    }

    ?>
    
    <body>

        <header style="text-align: center;">
            Welcome, <?php echo $_SESSION["name"];?>! Look, 3 random planets!<br/><br/><br/>
        </header>

        <div id="planets"></div>

        <button onclick="otherPlanets()">Other random planets</button>
        <div id="info"></div>
        
    </body>
</html>