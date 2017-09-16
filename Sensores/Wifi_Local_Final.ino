#include <SoftwareSerial.h>
SoftwareSerial ESP8266(10,11); // RX, TX

String server = "192.168.0.114";

////////////Variables del sensor de temperatura////////////////
const int SenTemp = A8;    //Pin del sensor de Temperatura
float LecTemp = 0;
float Temp = 0;
float TempC = 0;
float Temp_f=0;

////////////Variables del sensor de humedad////////////////
const int SenHum = A10;      //Pin analògico del sensor Humedad
int LecHum = 0;
float ValHum = 0;
float Hum = 0;  
float Hum_f=0;

///////////Ventilador//////////////////
const int Vent=47;

String cadena="";

void setup() {

  ESP8266.begin(9600);
  Serial.begin(9600);
  ESP8266.setTimeout(2000);
  
  //Verificamos si el ESP8266 responde
  ESP8266.println("AT");
  if(ESP8266.find("OK")){
    Serial.println("Respuesta AT correcto");
  }
  else{
    Serial.println("Error en ESP8266");
  }

  //-----Configuración de red-------//Podemos comentar si el ESP ya está configurado

    //ESP8266 en modo estación (nos conectaremos a una red existente)
    ESP8266.println("AT+CWMODE=1");
    if(ESP8266.find("OK"))
      Serial.println("ESP8266 en modo Estacion");
      
    //Nos conectamos a una red wifi 
    ESP8266.println("AT+CWJAP=\"Robotica\",\"P4t05155t34m\"");
    Serial.println("Conectandose a la red ...");
    ESP8266.setTimeout(10000); //Aumentar si demora la conexion
    if(ESP8266.find("OK"))
      Serial.println("WIFI conectado");
    else
      Serial.println("Error al conectarse en la red");
    ESP8266.setTimeout(2000);
    //Desabilitamos las conexiones multiples
    ESP8266.println("AT+CIPMUX=0");
    if(ESP8266.find("OK")){
      Serial.println("Multiconexiones deshabilitadas");
    }
  //------fin de configuracion-------------------

  delay(1000);
  
}

////////////Temperatura////////////////
void Temperatura(){
   LecTemp = analogRead(SenTemp);      //Se lee los valores del sensor de temperatura
   Temp = (LecTemp / 1023) * 5000;      //Se convierten los datos obtenidos a milivolts
   TempC = Temp / 10;                  //Se convierten los milivolts a grados centigrados

   Temp_f=TempC;
   TempC=0;
}

////////////Humedad////////////////
void Humedad(){
  LecHum = analogRead (SenHum);                   //Se lee los valores del sensor ed humedad
  //ValHum = (LecHum - 861) / 6.68;                 //Se obtiene el porcentaje
  Hum = map(LecHum,100,305,100,0);                  //Se invierte el porcentaje   
  if(Hum<0){
    Hum_f=0;
  }
  if(Hum>100){
    Hum_f=100;
  }
  if(Hum>=0){
    Hum_f=Hum;
    Hum=0;
  }

  //ValHum = map(LecHum,142,305,100,0);
}



void loop() {
  
  //--- programa----------------------
  
  //---------enviamos las variables al servidor---------------------
  
      //Nos conectamos con el servidor:
      
      ESP8266.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");
      if( ESP8266.find("OK"))
      {  
          Serial.println();
          Serial.println();
          Serial.println();
          Serial.println("ESP8266 conectado con el servidor...");   

          Humedad();
          delay(300);
          Temperatura();
    
          //Armamos el encabezado de la peticion http
          String peticionHTTP= "GET /?temperatura=";
          peticionHTTP=peticionHTTP+String(Temp_f)+"&humedad="+String(Hum_f)+" HTTP/1.1\r\n";
          peticionHTTP=peticionHTTP+"Host: 192.168.0.114\r\n\r\n";
          
          //Enviamos el tamaño en caracteres de la peticion http:  
          ESP8266.print("AT+CIPSEND=");
          ESP8266.println(peticionHTTP.length());

          //esperamos a ">" para enviar la petcion  http
          if(ESP8266.find(">")) // ">" indica que podemos enviar la peticion http
          {
            Serial.println("Enviando HTTP . . .");
            ESP8266.println(peticionHTTP);
            if( ESP8266.find("SEND OK"))
            {  
              Serial.println("Peticion HTTP enviada:");
              Serial.println();
              Serial.println(peticionHTTP);
              Serial.println("Esperando respuesta...");
              
              boolean fin_respuesta=false; 
              long tiempo_inicio=millis(); 
              cadena="";
              
              while(fin_respuesta==false)
              {
                  while(ESP8266.available()>0) 
                  {
                      char c=ESP8266.read();
                      Serial.write(c);
                      cadena.concat(c);  //guardamos la respuesta en el string "cadena"
                  }
                  //finalizamos si la respuesta es mayor a 500 caracteres
                  if(cadena.length()>500) //Pueden aumentar si tenen suficiente espacio en la memoria
                  {
                    Serial.println("La respuesta a excedido el tamaño maximo");
                    
                    ESP8266.println("AT+CIPCLOSE");
                    if( ESP8266.find("OK"))
                      Serial.println("Conexion finalizada");
                    fin_respuesta=true;
                  }
                  if((millis()-tiempo_inicio)>10000) //Finalizamos si ya han transcurrido 10 seg
                  {
                    Serial.println("Tiempo de espera agotado");
                    ESP8266.println("AT+CIPCLOSE");
                    if( ESP8266.find("OK"))
                      Serial.println("Conexion finalizada");
                    fin_respuesta=true;
                  }
                  if(cadena.indexOf("CLOSED")>0) //si recibimos un CLOSED significa que ha finalizado la respuesta
                  {
                    Serial.println();
                    Serial.println("Cadena recibida correctamente, conexion finalizada");         
                    fin_respuesta=true;
                  }
              }
    
              
            }
            else
            {
              Serial.println("No se ha podido enviar HTTP.....");
           }            
          }
      }
      else
      {
        Serial.println("No se ha podido conectarse con el servidor");
      }

     
  //-------------------------------------------------------------------------------

  delay(300000); //pausa de 10seg antes de conectarse nuevamente al servidor (opcional)
}

