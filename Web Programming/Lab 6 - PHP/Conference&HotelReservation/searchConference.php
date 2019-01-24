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

$sql = $conn->prepare("SELECT * FROM conferences WHERE City=? and Date=?");
$sql->bind_param("ss", $_SESSION["destination"], $_SESSION["date"]);
$sql->execute();
$res = $sql->get_result();

echo "Conference name <br/><select id=\"conferenceList\">";

while ($row = $res->fetch_assoc()) {
   echo "<option value=\"" . $row["Name"] . "\">" . $row["Name"] . "</option>";
}

$sql->close();
echo "</select>";

echo "<form>";
echo "<input type=\"button\" value=\"Reserve a slot\" onclick=\"reserveSlot()\">";
echo "</form>";

$conn->close();
?>