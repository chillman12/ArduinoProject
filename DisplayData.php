<?php 

//Please change the following values to your database. You can create free databse on https://remotemysql.com/
$servername = "xxxxxxxxxxxxxx"; //server name of database
$username = "xxxxxxxxxxxx"; //username of database
$password = "xxxxxxxxxxxxxx"; //password of database
$dbname = "xxxxxxxxxxxxx"; //database name
		// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);//now connect to your database

	echo "<style>table, th, td {
		border: 1px solid black;
	}
	</style>";

	echo "
	<div style='text-align:center'>
	<table style='text-align:center;margin-left:auto;margin-right:auto'>  <tr>
    <th>ID</th>
    <th>Temperature</th>
    <th>Humidity</th>
	<th>Time</th>
	<th>Hash check</th>
	</tr>";
	
	$sql = "SELECT * FROM ProjectData ORDER BY ID DESC LIMIT 20";
	
	$result = $conn->query($sql);
	


	if ($result->num_rows > 0) {
    while($row = $result->fetch_assoc()) {  
		
		if(trim(md5($row["Temp"])) == trim($row["hash"])){
			$check = "OK";
		}else{
			$check = "FAIL";
		}
	
		echo "<tr>
		<td>".$row["Id"]."</td>
		<td>".$row["Temp"]."</td>
		<td>".$row["Humidity"]."</td>
		<td>".$row["Time"]."</td>
		<td>".$check."</td>
		</tr>";  }
	}
	
	echo "</table></div>";
	
	$conn->close();
	
?>
