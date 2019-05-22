<?php require_once "scripts/header.php" ?>

<div class="plac_centered">
    <span class="head_main"> Financial Information </span>
    <span class="head_sub">  View information about your financial status, course fee, fines due etc. </span>
</div>


<div class="bordered margined_top padded">
    <span class="head_main_2">Fee Details</span>
    <span class="head_sub_2">View details about fees like how much has been paid, total fee etc. </span>
    <div class="margined_top"></div>

    <?php

    $msg = "";
    $disp_msg = "none";
    $hasDetails = false;

    $quer = "SELECT Student_Financial_Details.*, Semesters.sem_num FROM Student_Financial_Details JOIN Semesters ON Semesters.sem_id = Student_Financial_Details.sem_id WHERE Student_Financial_Details.roll_no =  ? ORDER BY Semesters.sem_num DESC; ";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    echo "<table>";

    echo "<tr> 
          <th style='width:20%'> Total Fee </th>     
          <th style='width:20%'> Paid Fee </th>          
          <th style='width:20%'> Scholorship </th>  
          <th style='width:20%'> Semester </th>  
          <th style='width:10%'> Full Paid </th>  
         </tr>";

    while($row = sqlsrv_fetch_array($res))
    {
       echo "<tr>";
    
       echo "<td style='width:20%'>" . $row['total_fee'] . " Rs</td>";

       echo "<td style='width:20%'>" . $row['paid_fee'] . " Rs</td>";

       echo "<td style='width:20%'>" . $row['scholorship'] . " Rs</td>";
       
       echo "<td style='width:20'>" . $row['sem_num'] . "</td>";
       
       echo "<td style='width:10'>" . ($row['total_fee'] == $row['paid_fee'] ? " <img src='assets/success.svg' width=12 height=12> <p class='success'> Yes </p>  " 
       :  "<img src='assets/error.svg' width=12 height=12> <p class='error'> No </p> " . "</td>")  . "</td>";

       echo "</tr>";

       if (!$hasDetails) $hasDetails = true;
    }

    echo "</table>";

    if (!$hasDetails) {
        $disp_msg = "inherit";
        $msg = "No fee details were found";
    }

    ?>

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/error.svg" ?> width=12 height=12 style="display: inline">
        <p class="error"> <?= $msg ?> </p>
    </div>
</div>

<div class="bordered margined_top padded">
    <span class="head_main_2">Fine Details</span>
    <span class="head_sub_2">View details about fine like the teacher who fined you and amount you were fined etc. </span>
    <div class="margined_top"></div>

    <?php

    $msg = "";
    $disp_msg = "none";
    $hasDetails = false;

    $quer = "SELECT Student_Fine_Details.*, Teachers.name FROM Student_Fine_Details  JOIN Teachers  ON Student_Fine_Details.teacher_id = Teachers.teacher_id WHERE Student_Fine_Details.roll_no = ?; ";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    echo "<table>";

    echo "<tr> 
          <th style='width:30%'> Fined By </th>     
          <th style='width:15%'> Amount </th>          
          <th style='width:15%'> Paid </th>  
          <th style='width:40%'> Reason </th>  
         </tr>";

    while($row = sqlsrv_fetch_array($res))
    {
       echo "<tr>";
    
       echo "<td style='width:30%'>" . $row['name'] . "</td>";

       echo "<td style='width:15%'>" . $row['amount'] . " Rs</td>";

       echo "<td style='width:15%'>" . (!$row['paid'] ? "<img src='assets/error.svg' width=12 height=12> <p class='error'> No </p>"
       : "<img src='assets/success.svg' width=12 height=12> <p class='success'> Yes </p> ") . "</td>";
       
       echo "<td style='width:40%'>" . $row['reason'] . "</td>";

       echo "</tr>";

       if (!$hasDetails) $hasDetails = true;
    }

    echo "</table>";

    if (!$hasDetails) {
        $disp_msg = "inherit";
        $msg = "No fine details were found";
    }

    ?>

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/error.svg" ?> width=12 height=12 style="display: inline">
        <p class="error"> <?= $msg ?> </p>
    </div>
</div>


<?php require_once "scripts/footer.php" ?>