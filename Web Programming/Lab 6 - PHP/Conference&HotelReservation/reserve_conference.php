<html>
    <head>
        <title>Reserve a seat on a conference</title>
        <link rel="stylesheet" type="text/css" href="style.css">
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script>
            $(document).ready(function() {
                console.log("got here");
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("conferences").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "searchConference.php", true);
                xhttp.send();
            });


            function reserveSlot() {
                var xhttp;
                $conferenceName = $("#conferenceList").val();
                console.log($conferenceName);

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("info").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "reserveSlot.php?conferenceName="+$conferenceName, true);
                xhttp.send();
            }

            function newFlight() {
                window.location.replace("reserve_flight.php");
            }

            function cancelAll() {
                var xhttp;
                console.log("canceling");

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        window.location.replace("reserve_flight.php");
                    }
                };
                xhttp.open("GET", "cancelAll.php", true);
                xhttp.send();
            }

            function showStatistics() {
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        document.getElementById("stats").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "showStats.php", true);
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
            Welcome, <?php echo $_SESSION["name"];?>! Choose a conference you'd like to attend!<br/><br/><br/>
        </header>

        <button type="button" onclick="showStatistics()">Show statistics</button>

        <div id="stats">
        </div>

        <div id="conferences">
        </div>

        <div id="info">
        </div>

    </body>
</html>