<?php
	session_start();
?>


<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<link href="https://fonts.googleapis.com/css2?family=Patrick+Hand&display=swap" rel="stylesheet"> 
	<link rel="stylesheet" href="styles.css">
</head>
<body>
	<div class="container">
		<div class="nav-wrapper">
			<div class="left-side">
				<div class="nav-link-wrapper active-nav-link">
					<a href="index.php">Home</a>
				</div>

				<div class="nav-link-wrapper">
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
						<a href="login.php">Login</a>
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
			<div class="portfolio-items-wrapper">
				<div class="portfolio-item-wrapper">
					<div class="porfolio-img-background" style="background-image:url(Images/Bar.jpg)"></div>

					<div class="img-text-wrapper">
						<div class="logo-wrapper">
							<img src="Images/logos/Logo49.svg">
							<div class="subtitle">
								Coming Soon: The Bar
							</div>
						</div>
					</div>
				</div>
				<div class="portfolio-item-wrapper">
					<div class="porfolio-img-background" style="background-image:url(Images/security.jpg)"></div>

					<div class="img-text-wrapper">
						<div class="logo-wrapper">
							<img src="Images/logos/Logo49.svg">
							<div class="subtitle">
								Coming Soon: Security
							</div>
						</div>
					</div>
				</div>
				<div class="portfolio-item-wrapper">
					<div class="porfolio-img-background" style="background-image:url(Images/Lights.jpg)"></div>

					<div class="img-text-wrapper">
						<div class="logo-wrapper">
							<img src="Images/logos/Logo49.svg">
							<div class="subtitle">
								Coming Soon: Lights
							</div>
						</div>
					</div>
				</div>
			</div>

		</div>
	
	</div>
</body>
<script>
	const portfolioItems = document.querySelectorAll('.portfolio-item-wrapper')

	portfolioItems.forEach(portfolioItem => {
		portfolioItem.addEventListener('mouseover', () =>{
			portfolioItem.childNodes[1].classList.add('img-darken');
		})

		portfolioItem.addEventListener('mouseout', () =>{
			portfolioItem.childNodes[1].classList.remove('img-darken');
		})
			
	})
</script>
</html>

