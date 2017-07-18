<?php 
	//0->id 1->temperatura 2->humendad 3->hora 4->fechas
	include ("prueba.php");

	$user = "root";
	$pass = "";
	$server = "localhost";
	$bd = "sensores";
	$conexion = mysql_connect($server,$user,$pass) or die ("error :c".mysql_error());
	mysql_select_db ($bd,$conexion) or die("error");

	$archivo = fopen("archivo.txt","r") or die ("Error al abrir el archivo");
	
	$valores = array();
	$texto = fgets($archivo);
	echo $texto."<br>";
	$tam=strlen($texto);
	echo "<br>".$tam."<br>";
	$pos = 0;
    $uno = 1;
    $dato=0;
    $cont = 0;

    while ($pos<=$tam) {
    	$x = substr($texto, $pos, 1); //variable, punto de inicio, numero de caracteres :D
    	if ($x<>',') {
			$valores[$dato] = $valores[$dato].$x;
    	}
    	else{
    		$dato++;
    	}
    	$pos++;
    }
    foreach ($valores as $claves => $elemento) {
    	echo "<br>".$claves." = ".$elemento;
    	if($elemento == 35 ){
    		$temp = $elemento;
    	}
    }
    mysql_query("INSERT INTO `datos`(`sen_temp`) VALUES ('".$temp."')",$conexion) or die ("Error");
    
	fclose($archivo);
	mysql_close($conexion) or die ("Error al desconectar de la base de datos");
	echo "<br>Se a desconectado de la base de datos";
 ?>    