<html>
    <head>
        <title>Reserve a flight</title>
        <link rel="stylesheet" type="text/css" href="style.css">
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script>
            function showFlights() {
                var xhttp;

                departure = document.getElementById("departure").value;
                destination = document.getElementById("destination").value;
                date = document.getElementById("date").value;

                xhttp = new XMLHttpRequest();
                xhttp.onreadystatechange = function() {
                    if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("flights").innerHTML = this.responseText;
                    }
                };
                xhttp.open("GET", "searchFlight.php?dep="+departure+"&dest="+destination+"&date="+date, true);
                xhttp.send();
            }


            function buyTicket() {
                var xhttp;
                $flightName = $("#flightList").val();
                console.log($flightName);

                xhttp = new XMLHttpRequest();
                xhttp.open("GET", "buyTicket.php?flightName="+$flightName, true);
                xhttp.send();
                window.location.replace("/Faculty@Conference&HotelReservation/reserve_hotel.php");
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
            Welcome, <?php echo $_SESSION["name"];?>! Choose a flight!<br/><br/><br/>
        </header>

        <form> 
        Departure: <input type="text" id="departure"><br/>
        Destination: <input type="text" id="destination"><br/>
        Date: <input type="date" id="date"><br/>
        <button type="button" onclick="showFlights()">Search flights</button>
        </form>

        <button type="button" onclick="showStatistics()">Show statistics</button>

        <div id="stats">
        </div>

        <div id="flights">
        </div>

    </body>
</html>