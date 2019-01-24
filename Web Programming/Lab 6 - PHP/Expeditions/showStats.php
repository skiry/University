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


$stmt = $conn->prepare("SELECT COUNT(*) as nr FROM `civilizations` WHERE homeplanetid=? AND type=?");
$dp = 0;
$type = 0;
$stmt->bind_param("ii", $_GET["id"], $type);
$stmt->execute();
$res = $stmt->get_result();
if ($row = $res->fetch_assoc()) {
    $t0 = $row["nr"];
}
$stmt->close();

$stmt = $conn->prepare("SELECT COUNT(*) as nr FROM `civilizations` WHERE homeplanetid=? AND type=?");
$dp = 0;
$type = 1;
$stmt->bind_param("ii", $_GET["id"], $type);
$stmt->execute();
$res = $stmt->get_result();
if ($row = $res->fetch_assoc()) {
    $t1 = $row["nr"];
}
$stmt->close();

$stmt = $conn->prepare("SELECT COUNT(*) as nr FROM `civilizations` WHERE homeplanetid=? AND type=?");
$dp = 0;
$type = 2;
$stmt->bind_param("ii", $_GET["id"], $type);
$stmt->execute();
$res = $stmt->get_result();
if ($row = $res->fetch_assoc()) {
    $t2 = $row["nr"];
}
$stmt->close();


$sql = $conn->prepare("SELECT * FROM planets WHERE id=?");
$sql->bind_param("i", $_GET["id"]);
$sql->execute();
$res = $sql->get_result();

if ($row = $res->fetch_assoc()) {
    echo $row["name"] . " is " . $row["description"] . " and its dominant civilization type is ";
    if( $t0 > $t1 )
    {
        if( $t0 > $t2 )
        {
            echo " the neutral one, with " . $t0 . " planets.";
        }
        else
        {
            echo " the one with 2, with " . $t2 . " planets.";
        }
    }
    else
    {
        if( $t1 > $t2 )
        {
            echo " the one with 1, with " . $t1 . " planets.";
        }
        else
        {
            echo " the one with 2, with " . $t2 . " planets.";
        }
    }
}

$sql->close();
$conn->close();
?>