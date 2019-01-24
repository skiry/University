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

$sql = $conn->prepare("SELECT ID, Slots, Name FROM conferences WHERE Name=?");
$sql->bind_param("s", $_GET["conferenceName"]);
$sql->execute();
$res = $sql->get_result();

if($row = $res->fetch_assoc()) {
    $id = $row["ID"];
    $_SESSION["lastConference"] = $row["Name"];

    if ($row["Slots"] == 0) {
        array_push($_SESSION["failures"], $_SESSION["lastConference"]);
        echo "No free slots on this conference. Flight and hotel reservation canceled. Look for another city/date <input type=\"button\" value=\"here\" onclick=\"cancelAll()\">.";
    }
    else {    
    array_push($_SESSION["successes"], $_SESSION["lastConference"]);
    $sql->close();
    $stmt = $conn->prepare("INSERT INTO conference_registration(IDConference,Client) VALUES(?, ?)");
    $stmt->bind_param("is", $id, $_SESSION["name"]);
    $stmt->execute();
    $_SESSION["lastConferenceReservationId"] = mysqli_insert_id($conn);
    $_SESSION["conferenceId"] = mysqli_insert_id($conn);

    $stmt->close();
    $stmt = $conn->prepare("UPDATE conferences SET Slots = Slots - 1 WHERE ID = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
    echo "Everything done ok. Look for another city <input type=\"button\" value=\"here\" onclick=\"newFlight()\">.";
    }

}
$conn->close();
?>