<?php
	session_start();
?>

<!DOCTYPE html>
<html lan="en" and dir="Itr">
<head>
	<meta charset="utf-8"/>
	<title>Login</title>
	<link href="https://fonts.googleapis.com/css2?family=Patrick+Hand&display=swap" rel="stylesheet">
	<link rel="stylesheet" href="styles.css">

</head>

<body>
	<div class="container">
			<div class="container">
		<div class="nav-wrapper">
			<div class="left-side">
				<div class="nav-link-wrapper active-nav-link">
					<a href="index.php">Home</a>
				</div>

				<div class="nav-link-wrapper">
					<a href="about.php">About</a>
				</div>

				<div class="nav-link-wrapper">
					<a href="login.php">Login</a>
				</div>
			</div>

			<div class="right-side">
				<div class="brand">
					<div>The Zeringue Home</div>
				</div>
			</div>
		</div>
		

		</div>
		<div class="content-wrapper">
			<div class ="two-column-wrapper">
				<form class="login-box" action="includes/signup.inc.php" method="POST">

						<h1>
							Sign up
						</h1>
						<input type="text" name="uid" placeholder="Enter Username" id="username">

						<input type="password" name="pwd" placeholder="Enter Password" id="password">

						<input type="password" name="pwdrepeat" placeholder="Re-Enter Password" id="pwdRepeat">

						<input type="text" name="email" placeholder="Enter Email (Optional)" id="email">

						<button type="submit" name="submit">Sign Up</button>


				</form>
				<form class="login-box" action="includes/login.inc.php" method="POST">

						<h1>
							Login
						</h1>
						<input type="text" name="uid" placeholder="Enter Username" id="username">

						<input type="password" name="pwd" placeholder="Enter Password" id="password">

						<button type="submit" name="submit">Login</button>


				</form>
			</div>
		</div>
	</div>

</body>

<script>
function validateUser(){
	var username=document.getElementById("username").Value;
	var password=document.getElementById("password").Value;

	if(username=="admin" && password==""){
		alert("login succesfull");
		return false;

	}
	else{
		alert("login failed");
		return false;
	}
}

</script>

</html>
