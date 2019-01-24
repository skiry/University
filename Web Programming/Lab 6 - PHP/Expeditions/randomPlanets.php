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

$sql = $conn->prepare("SELECT * FROM planets");
$sql->execute();
$res = $sql->get_result();
$randomNrs = array();
$done = 0;
if(count($_SESSION['planets']) >= $res->num_rows)
{
    $done = 1;
}
else
{
    $r = rand(0, $res->num_rows - 1);
    while(in_array($r, $_SESSION['planets'])){
        $r = rand(0, $res->num_rows - 1);
    }
    $array = $_SESSION['planets'];
    array_push($array, $r);
    $_SESSION['planets'] = $array;
    array_push($randomNrs, $r);

    if(count($_SESSION['planets']) >= $res->num_rows)
    {
        $done = 1;
    }
    else
    {
        $r = rand(0, $res->num_rows - 1);
        while(in_array($r, $_SESSION["planets"])){
            $r = rand(0, $res->num_rows - 1);
        }
        $array = $_SESSION['planets'];
        array_push($array, $r);
        $_SESSION['planets'] = $array;
        array_push($randomNrs, $r);
        
        if(count($_SESSION['planets']) >= $res->num_rows)
        {
            $done = 1;
        }
        else
        {
            $r = rand(0, $res->num_rows - 1);
            while(in_array($r, $_SESSION["planets"])){
                $r = rand(0, $res->num_rows - 1);
            }
            $array = $_SESSION['planets'];
            array_push($array, $r);
            $_SESSION['planets'] = $array;
            array_push($randomNrs, $r);

        }
    }
}
if ($done === 1)
{
    echo "Last planets refresh!";
}
$cnt = 0;
while ($row = $res->fetch_assoc()) {
    if(in_array($row["id"] - 1, $randomNrs)){
        echo "<li class=\"dot\" value=" . $row["id"] . " style=\"background-color:" . $row["color"] .
         ";position: absolute; top: " . rand(0,400) . "px; left: " . rand(0, 400) . "px;\" id=\"d" . $cnt++ . "\" onmouseover=\"showInfo(this)\" onmouseout=\"empty(this)\" onclick=\"addExpedition(this)\"></li>";
    }
}
 
 $sql->close();
 
$conn->close();
?>