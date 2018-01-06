<html>
<head>
<title>Servidor del D2</title>
</head>
<body>
    <?php
        $servername = "localhost";
        $username = "root";
        $password = "";
        $dbname = "equipo";

        $nom = $_GET['nombre'];
        $edad = $_GET['edad'];
        try {
          $conn = new mysqli($servername, $username, $password, $dbname);
          echo "Conexion realizada"."____";
        } catch (Exception $e) {
              echo "Nel prro";
        }


        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }
        $sql = "INSERT INTO amigos(nombre,edad) VALUES('$nom','$edad')";
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
