<?php

//include 'PhpSerial.php';
$comPort = "COM3";




// function test($arg)
// {
// 	global $comPort;
// 	$serial = new PhpSerial;

// 	$serial->deviceSet($comPort);
// 	$serial->deviceOpen('w+');

// 	//stream_set_timeout($serial->_dHandle, 10);

// 	//$serial->confBaudRate(9600);

// 	$arg =(int)$argv[1];

// 	$serial->sendMessage($arg);
// 	var_dump($serial->readPort());

// 	$serial->deviceClose();
// }


//allow cli input
// function sendToSerial($arg){
	// global $comPort;
	// fread($comPort);
	// $fp =fopen($comPort, "w+");
	// if( !$fp) {
	// 	echo "Error";die();
	// }
	// fwrite($fp,  $arg);
	// fclose($fp);
// }

if(php_sapi_name() === 'cli'){
	$arg = $argv[1];
	//sendToSerial($arg);
    //test($arg);
}

if(isset($_GET['value'])){
	global $comPort;

	$arg = (int)$_GET['value'];
	
	fread($comPort);
	$fp =fopen($comPort, "w+");
	if( !$fp) {
		echo "Error";die();
	}
	fwrite($fp,  $arg);

	fclose($fp);
	
	echo $arg;
}