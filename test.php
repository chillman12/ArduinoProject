<?php

//Please change the following values to your database. You can create free databse on https://remotemysql.com/

$servername = "xxxxxxxxxxxxxx"; //server name of database
$username = "xxxxxxxxxxxx"; //username of database
$password = "xxxxxxxxxxxxxx"; //password of database
$dbname = "xxxxxxxxxxxxx"; //database name

		// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);//now connect to your database
date_default_timezone_set('Canada/Eastern');
$t=time();
$time = date("Y-m-d h:i:s A",$t);

if(isset($_GET) && !empty($_GET["temp"])){
	if(!empty($_GET["hum"])){
		if(!empty($_GET["hash"])){
			echo "GET Temperature : ".$_GET["temp"]."<br>";
			echo "GET Humidity`: ".$_GET["hum"]."<br>";
			echo "GET Humidity`: ".$_GET["hash"];
			
			
			// Check connection
			if ($conn->connect_error) {
				die("Connection failed: " . $conn->connect_error);//if any error during connection then cut the //connection
			}

			$temp = $_GET["temp"];
			$hum = $_GET["hum"];
			$hash = $_GET["hash"];

			$sql = "INSERT INTO `ProjectData` (`Id`, `Temp`, `Humidity`, `Time`, `hash`) VALUES (NULL, '$temp', '$hum', '$time', '$hash')";

			if ($conn->query($sql) === TRUE) {

			} else {
				echo "Error: " . $sql . "<br>" . $conn->error;
			}
		}
	}			
}

if(isset($_POST) && !empty($_POST["temp"])){
	if(!empty($_POST["hum"])){
		if(!empty($_POST["hash"])){
			echo "POST Temperature : ".$_POST["temp"]."<br>";
			echo "POST Humidity`: ".$_POST["hum"]."<br>";
			echo "POST Humidity`: ".$_POST["hash"];
			
			// Check connection
			if ($conn->connect_error) {
				die("Connection failed: " . $conn->connect_error);//if any error during connection then cut the //connection
			}

			$temp = $_POST["temp"];
			$hum = $_POST["hum"];
			$hash = $_POST["hash"];
			
			$sql = "INSERT INTO `ProjectData` (`Id`, `Temp`, `Humidity`, `Time`, `hash`) VALUES (NULL, '$temp', '$hum', '$time', '$hash')";
			
			if ($conn->query($sql) === TRUE) {

			} else {
				echo "Error: " . $sql . "<br>" . $conn->error;
			}
		}
	}			
}

?>
