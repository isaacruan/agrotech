<html>
<head>
<title>Documentos Servicios Escolares</title>
</head>
<body>
    <?php
        $servername = "localhost";
        $username = "cetis155_admin";
        $password = "0spB0[UuODJe";
        $dbname = "cetis155_control";

        $tem = $_GET['temperatura'];
        //$pas = $_GET['password'];
        //$niv = $_GET['nivel'];
        
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        $sql = 'insert into sensores values('.$tem.')';
        //echo $sql;
        if ($conn->query($sql) === TRUE) {
            echo "Datos grabados ";
            $conn->close();
        } else {
             echo "Error: <br>" . $conn->error;
             $conn->close();
        }
    ?>
    
</body>
</html>