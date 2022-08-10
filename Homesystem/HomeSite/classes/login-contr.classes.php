<?php

class LoginContr extends Login {

	private $uid;
	private $pwd;

	public function __construct($uid, $pwd) {
			$this->uid = $uid;
			$this->pwd = $pwd;

	}

	public function loginUser(){
		if($this-> emptyInput() == false){
			// echo "Empty Input!"
			header("location: ../index.php?error=emptyinput");
			exit();
		}


		$this->getUser($this->uid,$this->pwd);
	}


	//checks to make sure all but the email has been filled out. (email is optional)
	private function emptyInput(){
		$result;
		if(empty($this->uid || $this->pwd)){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}


}