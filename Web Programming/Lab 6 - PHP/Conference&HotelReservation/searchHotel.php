<?php
session_start();

$servername = "localhost";
$user = "root";
$password = "";
$dbname = "hotel_conferences";

$conn = new mysqli($servername, $user, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = $conn->prepare("SELECT * FROM hotels WHERE City=? and Date=? and Rooms > 0");
$sql->bind_param("ss", $_SESSION["destination"], $_SESSION["date"]);
$sql->execute();
$res = $sql->get_result();

$ok = 0;

while ($row = $res->fetch_assoc()) {
    if ($ok == 0){
        echo "Hotel name <br/><select id=\"hotelList\">";
        $ok = 1;
    }
   echo "<option value=\"" . $row["Name"] . "\">" . $row["Name"] . "</option>";
}
$sql->close();
if ($ok == 0) {
    echo "No hotels with free rooms. Flight canceled. Look for another city <input type=\"button\" value=\"here\" onclick=\"cancelFlight()\">.";
}
else {
echo "</select>";

echo "<form>";
echo "<input type=\"button\" value=\"Make reservation\" onclick=\"makeReservation()\">";
echo "</form>";
}

$conn->close();
?>