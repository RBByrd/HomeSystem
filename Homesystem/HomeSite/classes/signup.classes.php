<?php

class Signup extends Dbh {

	protected function setUser($uid, $pwd, $email){
		$stmt = $this->connect()->prepare('INSERT INTO users (users_uid, users_pwd, users_email) VALUES (?, ?, ?);');

		$hashedPwd = password_has($pwd, PASSWORD_DEFAULT);



		
		if(!$stmt->execute(array($uid, $hashedPwd, $email))){
			$stmt = null;
			header("location: ../index.php?error=stmtfailed");
			exit();
		}

		//obtain a value 
		$resultCheck;
		if($stmt->rowCounts() > 0){
			$resultCheck = false;
		}
		else {
			$resultCheck = true;
		}

		return $resultCheck;
	}


	protected function checkUser($uid, $email){
		$stmt = $this->connect()->prepare('SELECT users_uid FROM users WHERE users_uid = ? OR users_email = ?;');

		//check if the user or email has been used already and send the new user back to the page with error message
		if(!$stmt->execute(array($uid, $email))){
			$stmt = null;
			header("location: ../index.php?error=stmtfailed");
			exit();
		}

		//obtain a value 
		$resultCheck;
		if($stmt->rowCounts() > 0){
			$resultCheck = false;
		}
		else {
			$resultCheck = true;
		}

		return $resultCheck;
	}

}