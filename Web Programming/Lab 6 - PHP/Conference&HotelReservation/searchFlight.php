<?php
session_start();

$departure = $_GET["dep"];
$destination = $_GET["dest"];
$date = $_REQUEST["date"];

$_SESSION["destination"] = $destination;
$_SESSION["date"] = $date;

$servername = "localhost";
$user = "root";
$password = "";
$dbname = "hotel_conferences";

$conn = new mysqli($servername, $user, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

echo "Flight name <br/><select id=\"flightList\">";

$sql = $conn->prepare("SELECT * FROM flights WHERE departure=? and destination=? and date=? and seats > 0");
$sql->bind_param("sss", $departure, $destination, $date);
$sql->execute();
$res = $sql->get_result();

while ($row = $res->fetch_assoc()) {
   echo "<option value=\"" . $row["Name"] . "\">" . $row["Name"] . "</option>";
}
$sql->close();
echo "</select>";

echo "<form>";
echo "<input type=\"button\" value=\"Buy ticket\" onclick=\"buyTicket()\">";
echo "</form>";

$conn->close();
?>