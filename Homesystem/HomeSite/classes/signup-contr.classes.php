<?php

class SignupContr {

	private $uid;
	private $pwd;
	private $pwdRepeat;
	private $email;

	public function __construct($uid, $pwd, $pwdRepeat, $email) {
			$this->uid = $uid;
			$this->pwd = $pwd;
			$this->pwdRepeat = $pwdRepeat;
			$this->email = $email;
			

	}

	//checks to make sure all but the email has been filled out. (email is optional)
	private function emptyInput(){
		$result;
		if(empty($this->uid || $this->pwd || $this->pwdRepeat)){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}

	//tests if the user ID has valid characters
	private function emptyInput(){
		$result;
		if(!preg_match("/^[a-zA-Z0-9]*$/",$this->uid)){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}

	//tests that if an email has been entered, it is a valid email.
	private function invalidEmail(){
		$result;
		if(!filter_var($this->email, FILTER_VALIDATE_EMAIL) && !empty($this->email)){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}

	private function pwdMatch(){
		$result;
		if($this->pwd !== $this->pwdRepeat)){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}

}