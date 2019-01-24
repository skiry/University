<html>
    <head>
        <title>Reserve a hotel</title>
        <link rel="stylesheet" type="text/css" href="style.css">
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script>
            $(document).ready(function() {
                console.log("got here");
                var xhttp;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("hotels").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "searchHotel.php", true);
                xhttp.send();
            });


            function makeReservation() {
                var xhttp;
                $hotelName = $("#hotelList").val();
                console.log($hotelName);

                xhttp = new XMLHttpRequest();
                xhttp.open("GET", "makeReservation.php?hotelName="+$hotelName, true);
                xhttp.send();
                window.location.replace("reserve_conference.php");
            }

            function cancelFlight() {
                var xhttp;
                console.log("canceling");

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                        window.location.replace("reserve_flight.php");
                    }
                };
                xhttp.open("GET", "cancelFlight.php", true);
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
            Welcome, <?php echo $_SESSION["name"];?>! Choose a hotel!<br/><br/><br/>
        </header>

        <button type="button" onclick="showStatistics()">Show statistics</button>

        <div id="stats">
        </div>

        <div id="hotels">
        </div>

    </body>
</html>