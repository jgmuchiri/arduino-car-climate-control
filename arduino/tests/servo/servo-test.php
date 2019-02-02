<?php
$comPort = "/dev/ttyACM0"; /*change to correct com port */

if (isset($_POST["rcmd"])) {
    $rcmd = $_POST["rcmd"];

    //1 = stop 5=right 6=left
    $fp = fopen($comPort, "w");
    fwrite($fp, $rcmd); /* this is the number that it will write */
    fclose($fp);

}
?>
<html>
<body>

<h2>Auto Control</h2>

<form method="post" action="">
    <input type="text" value="" name="rcmd">
    <button>Go</button>

</form>
</body>
</html>
