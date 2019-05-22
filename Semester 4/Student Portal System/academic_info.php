<?php require_once "scripts/header.php" ?>

<div class="plac_centered">
    <span class="head_main"> Academic Information </span>
    <span class="head_sub"> View details about your academic performance, grades, attendence etc. </span>
</div>

<div class="bordered margined_top padded">
    <span class="head_main_2">Result Details</span>
    <span class="head_sub_2">View details about grades you took in different courses  </span>
    <div class="margined_top"></div>

    <?php

    $msg = "";
    $disp_msg = "none";
    $hasDetails = false;

    $quer = "SELECT Student_Academic_Details.*, Semesters.sem_num, Semesters.sem_session FROM Student_Academic_Details JOIN Semesters ON Semesters.sem_id = Student_Academic_Details.sem_id WHERE Student_Academic_Details.roll_no =  ? ORDER BY Semesters.sem_num DESC;";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    echo "<table>";

    echo "<tr> 
          <th style='width:30%'> Course Name </th>     
          <th style='width:15%'> Semester </th>          
          <th style='width:15%'> Session </th>  
          <th style='width:15%'> Grade </th>  
          <th style='width:15%'> Passed </th>  
         </tr>";

    while($row = sqlsrv_fetch_array($res))
    {
       echo "<tr>";
    
       echo "<td style='width:30%'>" . $row['course_name'] . "</td>";

       echo "<td style='width:15%'>" . $row['sem_num'] . " </td>";

       echo "<td style='width:15%'>" . $row['sem_session'] . "</td>";

       echo "<td style='width:15%'>" . $row['grade'] . "</td>";

       echo "<td style='width:15%'>" . ($row['grade'] == "F" ? "<img src='assets/error.svg' width=12 height=12> <p class='error'> No </p>"
       : "<img src='assets/success.svg' width=12 height=12> <p class='success'> Yes </p> ") . "</td>";
       

       echo "</tr>";

       if (!$hasDetails) $hasDetails = true;
    }

    echo "</table>";

    if (!$hasDetails) {
        $disp_msg = "inherit";
        $msg = "No result details were found";
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
    <span class="head_main_2">Attendence Details</span>
    <span class="head_sub_2">View details about attendence specific to courses, like were you present etc . </span>
    <div class="margined_top"></div>

    <?php

    $msg = "";
    $disp_msg = "none";
    $hasDetails = false;

    $quer = "SELECT Student_Attendence_Details.*, Semesters.sem_num, Semesters.sem_session FROM Student_Attendence_Details  JOIN Semesters  ON Student_Attendence_Details.sem_id = Semesters.sem_id WHERE Student_Attendence_Details.roll_no = ? ORDER BY  Student_Attendence_Details.date DESC, Student_Attendence_Details.course_name DESC; ";

    $params = array($_SESSION['id']);
    $res = sqlsrv_query($conn, $quer, $params); 

    if (!$res) {
        echo "Could not query the database.\n";  
        die (print_r(sqlsrv_errors(), true));
    }

    echo "<table>";

    echo "<tr> 
          <th style='width:30%'> Course Name </th>     
          <th style='width:15%'> Semester </th>          
          <th style='width:15%'> Session </th>  
          <th style='width:15%'> Date </th>
          <th style='width:15%'> Status </th>  

         </tr>";

    while($row = sqlsrv_fetch_array($res))
    {
       echo "<tr>";
    
       echo "<td style='width:30%'>" . $row['course_name'] . "</td>";

       echo "<td style='width:15%'>" . $row['sem_num'] . "</td>";
       
       echo "<td style='width:15%'>" . $row['sem_session'] . "</td>";
       
       echo "<td style='width:15%'>" . $row['date']->format('d/m/Y') . "</td>";

       echo "<td style='width:15%'>" . (!$row['present'] ? "<img src='assets/error.svg' width=12 height=12> <p class='error'> Absent </p>"
                                                      : "<img src='assets/success.svg' width=12 height=12> <p class='success'> Present </p> ") . "</td>";
       
       echo "</tr>";

       if (!$hasDetails) $hasDetails = true;
    }

    echo "</table>";

    if (!$hasDetails) {
        $disp_msg = "inherit";
        $msg = "No attendence details were found";
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