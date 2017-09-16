/*Sensor de Temperatura y Humedad DHT11<br>Instrucciones:
Recuerda descargar la libreria DHT para poder utilizar este sensor
Conectaremos el Sensor DHT11 a 5v y el pin de señal a la entrada digital 7
*/
  
#define SSID "Robotica" //Nombre de la Red Wifi a la que nos conectamos
#define PASS "P4t05155t34m" //Contraseña de la Red Wifi
#define IP "192.168.0.62" // thingspeak.com
  
//Sustituir [WRITE_API_KEY] por la obtenida en thingspeak.com sin []
String GET_TEMP = "GET /?temperatura="; //Campo de temperatura
String GET_HUM = "GET /update?key=S05WWVIV8OUK4KFD&field2="; //Campo de humedad
  
  
////////////Variables del sensor de temperatura////////////////
const int SenTemp = A8;    //Pin del sensor de Temperatura
float LecTemp = 0;
float Temp = 0;
float TempC = 0;

  
  
void setup()
{
 
  
 //dht.begin(); //Se inicializa sensor DHT
 Serial.begin(115200); //Se inicializa el puerto Serial para comunicarse con el Modulo Wifi ESP8266
 Serial.setTimeout(4000); //Set el Timeout en 3 segundos para Serial.find()
 Serial.println("AT\r"); //PROBAR CON \n\r
  
 delay(2000);
  
 if(Serial.find("OK")){ //Verificar si Modulo Wifi responde
    if(!connectWiFi()){ //Conectarse a la red
       Serial.println("NO SE PUDO CONECTAR A RED WIFI");
    }
 } else {
    Serial.println("MODULO WIFI NO RESPONDE");
 }
}

void loop(){
   float h = millis(); // Lee la humedad
   float t = 0;        //Lee la temperatura

   Temperatura();
   Serial.print ("Temperatura: ");       //Se muestra la temperatura
   Serial.print (TempC);
   Serial.println (" C");
   t=TempC;


   char bufferTemp[8]; //Crear buffer temporal para convertir float a string
   String temperatura = dtostrf(t, 8, 3, bufferTemp); //Convertir de float a String 8 = longitud de String, 3 = numero de decimales. (e.g. 1234.567)
   updateTemp(temperatura); //Actualizar temperatura
 
   digitalWrite(13,HIGH);
   delay(5000); 
   /*/Si se hace mas pronto no se captura el Dato. Esperar 20 para estar seguros
  
   char bufferHum[8]; //Crear buffer temporal para convertir float a string
   String humedad = dtostrf(h, 8, 2, bufferHum); //Convertir de float a string 8 = longitud de String, 3 = numero de decimales. (e.g. 1234.567)
   updateHumedad(humedad); //Actualizar humedad
   digitalWrite(13,LOW);
   delay(20000); //Hacer una medicion cada 20 segundos
   */
}

////////////Temperatura////////////////
void Temperatura(){
   LecTemp = analogRead(SenTemp);      //Se lee los valores del sensor de temperatura
   Temp = (LecTemp / 1023) * 5000;      //Se convierten los datos obtenidos a milivolts
   TempC = Temp / 10;                  //Se convierten los milivolts a grados centigrados
}

  
void updateTemp(String temp){
   //String cmd="AT+CIPMUX=0";
   //Serial.println(cmd);
   String cmd = "AT+CIPSTART=\"TCP\",\""; //Crear el comando para comenzar una conexion TCP
   cmd += IP; //IP del sitio a conectarse (thingspeak.com)
   cmd += "\",22"; //Puerto (80)
   Serial.println(cmd); //Crear conexion
   delay(2000); //Darle 2 segundos para responder
   if(Serial.find("ERROR")){
      Serial.println("error de conexion a IP");
      return; //No se pudo conectar
   }
     
   temp.trim(); //Remover espacios e.g. "____30.00" >> "30.00"
  
   cmd = GET_TEMP; //Crear datos a enviar
   cmd += temp; //Agregar la temperatura leida
   cmd += "\r\n"; //Agregar caracteres de newline y Carriage return
   
//   cmd *= " HTTP/1.1\r\n";
//   cmd *= "Host: 192.168.0.102\r\n\r\n";

  
   Serial.print("AT+CIPSEND="); //Indicar cuantos datos se enviaran por TCP
   Serial.println(cmd.length()); //Tamaño de los datos a enviar por TCP
   delay(2000);
   if(Serial.find(">")){
      Serial.print(cmd); //Enviar datos
   }else{
       Serial.println("AT+CIPCLOSE"); //No se pudo ejecutar, cerrar conexion TCP
      Serial.println("no puede enviar datos     "+cmd); //No se pudo ejecutar, cerrar conexion TCP
   }
}
  
void updateHumedad(String humedad){
   String cmd = "AT+CIPSTART=\"TCP\",\"";
   cmd += IP;
   cmd += "\",22";
   Serial.println(cmd);
   delay(2000);
  
   if(Serial.find("ERROR")){
      Serial.println("ERROR DE CONEXION A IP"); 
      return;
   }
 
   humedad.trim();
  
   cmd = GET_HUM;
   cmd += humedad;
   cmd += "\r\n";
   Serial.print("AT+CIPSEND=");
   Serial.println(cmd.length());
   delay(2000);
   if(Serial.find(">")){
      Serial.print(cmd);
   }else{
      Serial.println("AT+CIPCLOSE");
   }
}

//Funcion para crear conexion Wifi. Regresa true si se conecta exitosamente, si no false.
boolean connectWiFi(){
  
   Serial.println("AT+CWMODE=3"); //Configurar Modulo Wifi ESP8266 en Modo 3 = Station + Access Point (Trasmitir y Recibir)
   delay(2000); //Darle tiempo para ejecutar comando
   String cmd="AT+CWJAP=\""; //
   cmd+=SSID;
   cmd+="\",\"";
   cmd+=PASS;
   cmd+="\"";
   //cmd = AT+CWJAP="SSID","PASS"
   Serial.println(cmd);
   delay(10000); //Darle 10 segundos para conectarse
   if(Serial.find("OK")){ 
      return true; //Conexión existosa
   }else{
      return false; //No se pudo conectar
   }
}
