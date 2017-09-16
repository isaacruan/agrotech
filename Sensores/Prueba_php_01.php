<?php 

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
    $posx=0;
    $posy=1;
    $uno = 1;
    $dato=0;

    while ($pos<=$tam) {
    	$x = substr($texto, $posx, $posy); //variable, punto de inicio, numero de caracteres :D
    	if ($x<>',') {
    		$valores[$dato] = $x;
    		//mysql_query("INSERT INTO `datos`(`sen_temp`) VALUES ('".$valores[$dato]."')", $conexion) or die ("Error al agregar el dato");
    		echo $valores[$dato]; // 0->id 1->temperatura 2->humendad 3->hora 4->fechaz
    	}
    	else{
    		$dato=$dato+1;
    	}
    	$pos=$pos+1;
    $dato=0;
    }
    foreach ($valores as $claves => $elemento) {
    	echo "<br>".$claves." = ".$elemento;
    }
  	echo "<br>".$valores[0];
	fclose($archivo);
	mysql_close($conexion);
	echo "<br>Se a desconectado de la base de datos";
 ?>    
