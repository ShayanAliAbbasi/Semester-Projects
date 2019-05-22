<?php session_start() ?>
<?php require_once "scripts/connection.php" ?>
<?php
   
$uri = $_SERVER['REQUEST_URI'];
$tokens = explode("/", $uri);
$curPage = explode(".", end($tokens));
$pageName = $curPage[0];

function test_input($data)
{
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

if (!isset($_SESSION['id'])) { sleep(2); header("Location: login.php"); }

?>

<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">

    <link rel="shortcut icon" href="assets/logo.png">
    <link rel="stylesheet" href="styles/main.css">

    <script>

    window.addEventListener('scroll', () => {
        if (window.scrollY !== 0) {
            document.getElementsByTagName("header")[0].style.borderBottom = "1px solid rgba(0, 0, 0, 0.20)";
            document.getElementsByTagName("header")[0].style.boxShadow = "0px 3px 5px 0px rgba(0, 0, 0, 0.13)";
            document.getElementById("to_top").style.display = "inherit";
        } else {
            document.getElementsByTagName("header")[0].style.borderBottom = "none";
            document.getElementsByTagName('header')[0].style.boxShadow = 'none';
            document.getElementById("to_top").style.display = "none";
        }
    })

    </script>

    <title>Student Portal</title>

</head>

<body>

    <span class="top" style="display:none;"></span>

    <header>
        <div class="logo_placeholder">
            <a href="home.php">
                <img src="assets/logo.png" width="50" height="40">
                <span>Student Portal</span>
            </a>
        </div>

        <div id="announc_plac">
            <marquee id="announc"> Currently there are no important announcements! </marquee>
        </div> 
     
        <a href="scripts/logout.php" class="button float_right right_padded left_padded" style="border-bottom-left-radius: 50px">
            <img class="nav_icon centered" src="assets/logout.svg" width="20" height="20">
            <span class="nav_text centered">Log Out</span>
        </a>

    </header>

    <nav>
        <a href="home.php" class = " <?php echo ($pageName == 'home') ?  'current' : ''; ?> ">
            <img class="nav_icon" src="assets/home.svg" width="20" height="20">
            <span class="nav_text">Home</span>
        </a>
        <a href="personal_info.php" class = " <?php echo ($pageName == 'personal_info') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/person.svg" width="20" height="30">
            <span class="nav_text">Personal Information</span>
        </a>
        <a href="academic_info.php" class = " <?php echo ($pageName == 'academic_info') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/academy.svg" width="20" height="20">
            <span class="nav_text">Academic Information</span>
        </a>
        <a href="financial_info.php" class = " <?php echo ($pageName == 'financial_info') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/finance.svg" width="20" height="20">
            <span class="nav_text">Financial Information</span>
        </a>
        <a href="library_info.php" class = " <?php echo ($pageName == 'library_info') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/library.svg" width="20" height="20">
            <span class="nav_text">Library Information</span>
        </a>
        <a href="transfered_courses.php" class = " <?php echo ($pageName == 'transfered_courses') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/transfer.svg" width="20" height="20">
            <span class="nav_text">Transfered Courses</span>
        </a>

        <br />
        <hr style="border:none; border-bottom: 1px solid rgba(0, 0, 0, 0.15)" />
        <br />

        <!-- <a href="enrollment.php" class = " <?php echo ($pageName == 'enrollment') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/enroll.svg" width="20" height="20">
            <span class="nav_text">Enrollment</span>
        </a> -->
        <a href="change_email.php" class = " <?php echo ($pageName == 'change_email') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/email.svg" width="20" height="20">
            <span class="nav_text">Change Email</span>
        </a>
        <a href="change_pass.php" class = " <?php echo ($pageName == 'change_pass') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/cog.svg" width="20" height="20">
            <span class="nav_text">Change Password</span>
        </a>
        <a href="change_pic.php" class = " <?php echo ($pageName == 'change_pic') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/pic.svg" width="20" height="20">
            <span class="nav_text">Change Picture</span>
        </a>
        <a href="update_info.php" class = " <?php echo ($pageName == 'update_info') ? 'current' : ''; ?> ">
            <img class="nav_icon" src="assets/edit.svg" width="20" height="20">
            <span class="nav_text">Update Personal Info</span>
        </a>    
    </nav>

    <a id="to_top" href="#top">&uarr;</a>

    <div id="main_content">
    
    <?php

    # <!-- The main content of sub-pages will be included in this div -->
    # <!-- Div closed in footer.php -->

    ?>