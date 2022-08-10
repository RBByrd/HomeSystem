<?php
	session_start();
?>

<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<title>About</title>
	<link href="https://fonts.googleapis.com/css2?family=Patrick+Hand&display=swap" rel="stylesheet">
	<link rel="stylesheet" href="styles.css">
</head>
<body>
	<div class="container">
		<div class="nav-wrapper">
			<div class="left-side">
				<div class="nav-link-wrapper">
					<a href="index.php">Home</a>
				</div>

				<div class="nav-link-wrapper active-nav-link">
					<a href="about.php">About</a>
				</div>

				<?php
				if(isset($_SESSION["userid"])){
				?>
					<div class="nav-link-wrapper">
						<a href="includes/logout.inc.php">Logout</a>
					</div>
				<?php
				}
				else
				{
				?>
					<div class="nav-link-wrapper">
						<a href="Login.php">Login</a>
					</div>
				<?php
				}	
				?>
				
			</div>

			<div class="right-side">
				<div class="brand">
					<?php
						if(isset($_SESSION["userid"])){
					?>
						<div>The Zeringue home welcomes you <?php echo $_SESSION["useruid"]; ?> </div>
					<?php
					}
					else
					{
					?>
						<div>The Zeringue home</div>
					<?php
					} 
					?>
				</div>
			</div>
		</div>
		
		<div class="content-wrapper">
			<div class ="two-column-wrapper">
				<div class="profile-image-wrapper">
				
						<img src="Images/profile.jpg">
				</div>

				<div class="profile-content-wrapper">

					<h1>Welcome to our virtual home.</h1>

					<p>Lindsey and Ben have lived in this home since August 2021. We worked hard to make this home have a welcoming feel and match our styles.</p>

					<p> This page will let you know about some of the basics of the home. Of course you can ask us any of these questions, but for ease of use here is some commonly asked questions.</p>
				</div>

				<div class="profile-content-wrapper">
					<h1>First Floor Layout.</h1>

					<p>This is a split level home built in 1966. "Split level" reflects the home's use of a roughly 2 and a half foot change in height when transitioning from the living room to rest of the first floor. There are a few advatages to this. The open consept feel between the living and dining room, while simulatiously maintaing maintaining a barrier. This intermediate change also decreases the number of steps required to move to the second floor saving some sqaure footage for the bedrooms.  The raised living room is also less likely to flood in such an event.</p>



				</div>
			</div>

		</div>
	
	</div>
</body>
<script>

</script>
</html>

