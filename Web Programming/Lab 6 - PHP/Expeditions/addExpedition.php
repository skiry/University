<?php
session_start();

$servername = "localhost";
$user = "root";
$password = "";
$dbname = "planets";

$conn = new mysqli($servername, $user, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = $conn->prepare("SELECT * FROM astronauts");
$sql->execute();
$res = $sql->get_result();
$id = 0;
while ($row = $res->fetch_assoc()) {
    echo $row["name"] . $_SESSION["name"];
    if ($row["name"] == $_SESSION["name"])
    {
        $id = $row["id"];
        $civilization = $row["civilizationid"];
    }
}
$n = 1;
if($id != 0) {    
    $sql->close();
    
    $stmt = $conn->prepare("SELECT * FROM `civilizations` WHERE id=?");
    $dp = 0;
    $stmt->bind_param("i", $civilization);
    $stmt->execute();
    $res = $stmt->get_result();
    if ($row = $res->fetch_assoc()) {
        $homeplanetid = $row["homeplanetid"];
        $type = $row["type"];
    }
    $stmt->close();

    $stmt = $conn->prepare("SELECT COUNT(*) as nr FROM `civilizations` WHERE homeplanetid=?");
    $dp = 0;
    $stmt->bind_param("i", $_GET["id"]);
    $stmt->execute();
    $res = $stmt->get_result();
    if ($row = $res->fetch_assoc()) {
        $n = $row["nr"];
    }
    $stmt->close();

    $m = 0;
    $stmt = $conn->prepare("SELECT COUNT(*) as nr FROM `civilizations` WHERE homeplanetid=? AND type=?");
    $dp = 0;
    $enemy = 3 - $type;
    $stmt->bind_param("ii", $_GET["id"], $enemy);
    $stmt->execute();
    $res = $stmt->get_result();
    if ($row = $res->fetch_assoc()) {
        $m = $row["nr"];
    }
    $stmt->close();

    $stmt = $conn->prepare("INSERT INTO expeditions(astronautid,planetid,deathprobability) VALUES(?, ?, ?)");
    if($n !== 0){
        $dp = $m / $n;
    }
    else {
        $dp = 0;
    }
    $stmt->bind_param("iid", $id, $_GET["id"], $dp);
    $stmt->execute();
    $stmt->close();
}
$conn->close();
?>