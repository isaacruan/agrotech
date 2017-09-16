
////////////Variables del sensor de temperatura////////////////
const int SenTemp = A15;    //Pin del sensor de Temperatura
float LecTemp = 0;
float Temp = 0;
float TempC = 0;

////////////Variables del sensor de humedad////////////////
const int SenHum = A8;      //Pin del sensor de Humedad
int LecHum = 0;
//float ValHum = 0;
float Hum = 0;

////////////Temperatura////////////////
void Temperatura(){
  LecTemp = analogRead(SenTemp);      //Se lee los valores del sensor de temperatura
  Temp = (LecTemp / 1023) * 5000;      //Se convierten los datos obtenidos a milivolts
  TempC = Temp / 10;                  //Se convierten los milivolts a grados centigrados
  Serial.print ("Temperatura: ");       //Se muestra la temperatura
  Serial.print (TempC);
  Serial.println (" C");
}

////////////Humedad////////////////
void Humedad(){
  LecHum = analogRead (SenHum);       //Se lee los valores del sensor ed humedad
  //ValHum = 1023 - LecHum;             //Se obtiene la diferencia 
  Hum = LecHum / 4.7;                 //Se obtiene el porcentaje de humedad

  if(LecHum<=570){                    //Si el sensor muestra datos menores a 570 significa que esta en agua
    Serial.println ("Humedad: 100%");
  }

  if(LecHum>570 ){                     //Si el sensor muestra datos mayores a 570 
    Serial.print ("Humedad: ");       //Se muestra el porcentaje de humedad
    Serial.print (Hum);
    Serial.println (" %");
  }
}

void setup() {
  Serial.begin (9600);
}

void loop() {
  Temperatura();
  Humedad();

  delay(800);
}

