<?php require_once "scripts/header.php" ?>


<div class="plac_centered">
    <span class="head_main"> Personal Information </span>
    <span class="head_sub">  View information about yourself stored in our record, your contact details etc. </span>
</div>


<div class="bordered margined_top padded">
    <span class="head_main_2">Personal Details </span>
    <span class="head_sub_2">View your summarized information stored in our records </span>
    <div class="margined_top"></div>

    <?php

    $quer = "SELECT * FROM Students WHERE roll_no = ?";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    $row = sqlsrv_fetch_array($res);

    echo "<table>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Name </th>";
    echo "<td>" . $row['name'] . "</td>";
    echo "</tr>";

    echo "<tr>";
    echo "<th style='width: 42%'> Father Name </th>";
    echo "<td>" . $row['father_name'] . "</td>";
    echo "</tr>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Roll Number</th>";
    echo "<td> ". strtoupper($row['roll_no']) . "</td>";
    echo "</tr>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Joined </th>";
    echo "<td>" . $row['session'] . "</td>";
    echo "</tr>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Gender </th>";
    echo "<td>" . ($row['gender'] == "M" ? "Male ":"Female") . "</td>";
    echo "</tr>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Class</th>";
    echo "<td> ". $row['dep_name'] . "</td>";
    echo "</tr>";
        
    echo "<tr>";
    echo "<th style='width: 42%'> Grade</th>";
    echo "<td> ". ($row['cgpa'] <= 2.0 ? "<img src='assets/error.svg' width=12 height=12> <p class='error'>" . $row['cgpa'] . "</p>"
                                      : "<img src='assets/success.svg' width=12 height=12> <p class='success'>" . $row['cgpa'] . "</p> ") . "</td>";
    echo "</tr>";

    echo "</table>";

    ?>


</div>

<div class="bordered margined_top padded">
    <span class="head_main_2">Contact Information </span>
    <span class="head_sub_2">View your contact information stored in our record </span>
    <div class="margined_top"></div>

    <?php

    $quer = "SELECT * FROM Student_Contact_Details WHERE roll_no = ?";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    $row = sqlsrv_fetch_array($res);

    echo "<table>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Email </th>";
    echo "<td>" . $row['email_address'] . "</td>";
    echo "</tr>";

    echo "<tr>";
    echo "<th style='width: 42%'> Address </th>";
    echo "<td>" . $row['postal_address'] . "</td>";
    echo "</tr>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Phone</th>";
    echo "<td> ". ($row['phone_num1'] ? "0":""). $row['phone_num1'] . "</td>";
    echo "</tr>";
    
    echo "<tr>";
    echo "<th style='width: 42%'> Landline </th>";
    echo "<td>" . ($row['phone_num2'] ? "0":""). $row['phone_num2'] . "</td>";
    echo "</tr>";
    
    echo "</table>";

    ?>

</div>

<div class="bordered margined_top padded plac_centered" style="box-sizing:border-box;">

    <span class="head_main_2" style="text-align: left">Update Information </span>
    <span class="head_sub_2" style="text-align: left"> Update contact information, picture, password, email and personal information</span>

    <div class="margined_top"></div>
    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Update Personal Info</span>
            <span class="head_sub_2">Update your personal information stored in our record, like contact details, address etc.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/edit.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="update_info.php">Update Personal Info</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
            <span class="head_main_2">Change Email</span>
            <span class="head_sub_2">Change your email where important notices and forgotten password will be send.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/email.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="change_email.php">Change Email</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Change Password</span>
            <span class="head_sub_2">Change your portal's password to a stronger one to keep your account secure.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/password.png" width=96 height=96>
        </div>
        <a class="button_bottom padded" href="change_pass.php">Change Password</a>
    </div>

    <div class="card">
        <div class="card_plac_left padded">
        <span class="head_main_2">Change Profile Picture</span>
            <span class="head_sub_2">Change your profile picture to a more recent one, to avoid any identification issues.</span>
        </div>
        <div class="card_plac_right">
            <img src="assets/picture.png" width=94 height=94>
        </div>
        <a class="button_bottom padded" href="change_pic.php">Change Profile Pic</a>
    </div>

</div>

<?php require_once "scripts/footer.php" ?>