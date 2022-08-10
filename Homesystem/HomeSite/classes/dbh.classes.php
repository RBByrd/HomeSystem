<?php

class Dbh {


	protected function connect() {
		try{
			$username = "root";
			$password = "excalibur22";
			$dbh = new PDO('mysql:host=localhost;dbname=houselogin', $username, $password);
			return $dbh;
		}
		catch(PDOException $e) {
			print "Error!".$e->getMessage() . "<br/>";
			die();
		}
	}

}