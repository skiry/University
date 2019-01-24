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

$sql = $conn->prepare("SELECT ID FROM flights WHERE Name=?");
$sql->bind_param("s", $_GET["flightName"]);
$sql->execute();
$res = $sql->get_result();

if($row = $res->fetch_assoc()) {
    $id = $row["ID"];

    $sql->close();
    $stmt = $conn->prepare("INSERT INTO flight_reservations(IDFlight,Client) VALUES(?, ?)");
    $stmt->bind_param("is", $id, $_SESSION["name"]);
    $stmt->execute();
    $_SESSION["lastFlightReservationId"] = mysqli_insert_id($conn);
    $_SESSION["flightId"] = $id;

    $stmt->close();
    $stmt = $conn->prepare("UPDATE flights SET Seats = Seats - 1 WHERE ID = ?");
    $stmt->bind_param("s", $id);
    $stmt->execute();

}
$conn->close();
?>