<?php
session_start();

echo $_SESSION["lastFlightReservationId"] . " " . $_SESSION["flightId"];

$servername = "localhost";
$user = "root";
$password = "";
$dbname = "hotel_conferences";

$conn = new mysqli($servername, $user, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = $conn->prepare("DELETE FROM flight_reservations WHERE ID=?");
$sql->bind_param("i", $_SESSION["lastFlightReservationId"]);
$sql->execute();
$sql->close();

$stmt = $conn->prepare("UPDATE flights SET Seats = Seats + 1 WHERE ID = ?");
$stmt->bind_param("i", $_SESSION["flightId"]);
$stmt->execute();
$stmt->close();

$sql = $conn->prepare("DELETE FROM hotel_reservations WHERE ID=?");
$sql->bind_param("i", $_SESSION["lastHotelReservationId"]);
$sql->execute();
$sql->close();

$stmt = $conn->prepare("UPDATE hotels SET Rooms = Rooms + 1 WHERE ID = ?");
$stmt->bind_param("i", $_SESSION["hotelId"]);
$stmt->execute();
$stmt->close();

$conn->close();
?>