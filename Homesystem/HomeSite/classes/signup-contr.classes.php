<?php

class SignupContr extends Signup {

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

	public function signupUser(){
		if($this-> emptyInput() == false){
			// echo "Empty Input!"
			header("location: ../index.php?error=emptyinput");
			exit();
		}
		if($this-> invalidUid() == false){
			// echo "Invalid Username!"
			header("location: ../index.php?error=username");
			exit();
		}
		if($this-> invalidEmail() == false){
			// echo "Invalid Email!"
			header("location: ../index.php?error=email");
			exit();
		}
		if($this-> pwdMatch() == false){
			// echo "Passwords don't match!"
			header("location: ../index.php?error=passwordmatch");
			exit();
		}
		if($this-> uidTakenCheck() == false){
			// echo "Username or Email taken!"
			header("location: ../index.php?error=useroremailtaken");
			exit();
		}

		$this->setUser($this->uid,$this->pwd,$this->email);
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
	private function invalidUid(){
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

	//tests that the new passwords match
	private function pwdMatch(){
		$result;
		if($this->pwd !== $this->pwdRepeat){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}

	//checks that the user name or email hasn't been used already
	private function uidTakenCheck(){
		$result;
		//uses checkUser function in  the signup.classes.php file
		if(!$this->checkUser($this->uid, $this->email)){
			$result = false;
		}
		else {
			$result = true;
		}
		return $result;
	}

}