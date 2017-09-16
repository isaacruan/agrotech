
////////////Variables del sensor de temperatura////////////////
const int SenTemp = A8;    //Pin del sensor de Temperatura
float LecTemp = 0;
float Temp = 0;
float TempC = 0;

////////////Variables del sensor de humedad////////////////
const int SenHum = A10;      //Pin del sensor de Humedad
int LecHum = 0;
float ValHum = 0;
float Hum = 0;
int tiempo=0;
int t_ant=0;


void setup() {
  Serial.begin (9600);
}

void loop() {
  tiempo=millis();
  if (((tiempo-t_ant)>=3000) && ((tiempo-t_ant)<=3100)) {
      Temperatura();   
  }
  if (((tiempo-t_ant)>=8000)  && ((tiempo-t_ant)<=8100)){
        Humedad();
        t_ant=millis();
  }
  
}

////////////Temperatura////////////////
void Temperatura(){
  LecTemp = analogRead(SenTemp);      //Se lee los valores del sensor de temperatura
  Temp = (5.0 * LecTemp * 100)/1024.0;      //Se convierten los datos obtenidos a milivolts
  Serial.print ("Temperatura: ");       //Se muestra la temperatura
  Serial.print (Temp);
  Serial.println (" C");
}

////////////Humedad////////////////
void Humedad(){
  LecHum = analogRead (SenHum);                   //Se lee los valores del sensor ed humedad
  /*SenHum = map(LecHum,0,1023,1023,0);             //Se obtiene la diferencia 
  Hum = (SenHum - 270) / 4.2;*/                       //Se obtiene el porcentaje de humedad
  Serial.print("Humedad: ");
  Serial.println(LecHum);
  /*if(LecHum<=570){                    //Si el sensor muestra datos menores a 570 significa que esta en agua
    Serial.println ("Humedad: 100%");
  }

  if(LecHum>570){                     //Si el sensor muestra datos mayores a 570 
    Serial.print ("Humedad: ");       //Se muestra el porcentaje de humedad
    Serial.print (Hum);
    Serial.println (" %");
  }

  if(LecHum<=200){
    Serial.println (">> El sensor de humedad esta desconectado <<");
  }
*/
}
