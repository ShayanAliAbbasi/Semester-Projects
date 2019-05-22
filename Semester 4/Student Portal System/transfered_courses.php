<?php require_once "scripts/header.php" ?>

<div class="plac_centered">
    <span class="head_main"> Transfered Courses </span>
    <span class="head_sub"> View details of courses that you have transfered </span>
</div>

<div class="margined_top bordered padded">

    <span class="head_main_2" style="text-align: left">Transfered Courses Details </span>
    <span class="head_sub_2">Here are details of all courses you have transfered </span>
    
    <div class="margined_top">
    
    <?php
    
    $msg = "";
    $disp_msg = "none";
    $hasDetails = false;

    $quer = "SELECT * FROM Student_Transfered_Courses WHERE roll_no = ?;";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    echo "<table>";

    echo "<tr> 
          <th style='width:40%'> Course Name </th>     
          <th style='width:25%'> Grade </th>          
          <th style='width:35%'> Transfered From </th>  
         </tr>";

    while($row = sqlsrv_fetch_array($res))
    {
       echo "<tr>";
    
       echo "<td style='width:40%'>" . $row['course_name'] . "</td>";

       echo "<td style='width:25%'>" . $row['grade'] . "</td>";

       echo "<td style='width:35%'>" . $row['trans_from'] . "</td>";

       echo "</tr>";

       if (!$hasDetails) $hasDetails = true;
    }

    echo "</table>";

    if (!$hasDetails) {
        $disp_msg = "inherit";
        $msg = "You haven't transfered any courses";
    }
    ?>

    </div>

</div>

<div class="bordered margined_top" style=" display: <?= $disp_msg ?>; ">
    <span class="padded head_main_2">Message</span>
    <div style="padding: 6px 0px 26px 10px;">
        <img src=<?= "assets/error.svg" ?> width=12 height=12 style="display: inline">
        <p class="error"> <?= $msg ?> </p>
    </div>
</div>


<?php require_once "scripts/footer.php" ?>
