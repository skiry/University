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

$sql = $conn->prepare("SELECT ID FROM hotels WHERE Name=?");
$sql->bind_param("s", $_GET["hotelName"]);
$sql->execute();
$res = $sql->get_result();

if($row = $res->fetch_assoc()) {
    $id = $row["ID"];

    $sql->close();
    $stmt = $conn->prepare("INSERT INTO hotel_reservations(IDHotel,Client) VALUES(?, ?)");
    $stmt->bind_param("is", $id, $_SESSION["name"]);
    $stmt->execute();
    $_SESSION["lastHotelReservationId"] = mysqli_insert_id($conn);
    $_SESSION["hotelId"] = $id;

    $stmt->close();
    $stmt = $conn->prepare("UPDATE hotels SET Rooms = Rooms - 1 WHERE ID = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();

}
$conn->close();
?>