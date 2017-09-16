////////////////////VARIABLES DEL SENSOR DE TEMPERATURA/////////////////////
int tempC;
int lecTemp;
int temPin = A9; //pin analogico del sensor 
int exttemp=0;
int temp=0;  
/////////////////RELEVADOR//////////////////////////////////////////////////
const int rele = 52; //pin digital del relevador 
//////////////////VARIABLES DEL SENSOR DE HUMEDAD///////////////////////////
byte humPin = A8; //pin analogico del sensor 
byte humVcc = 33; //pin digital del sensor 
int exthumanalog=0;
int auxhum=0;
/////////////////////FUNCIONES CONTROLADORAS DE LOS SENSORES////////////////
void LM35(){
 lecTemp = analogRead(temPin);
 tempC = lecTemp/9.31;        //Se convierte la lectura del sensor a grados centigrados
 temp=lecTemp;
 exttemp = tempC;
 Serial.println("Sensor de temperatura :");
 Serial.print(lecTemp);
 Serial.print(" C\n");
}
void YL69(){
 digitalWrite(humVcc, HIGH);
 delay(500);
 int val = analogRead(humPin);
 digitalWrite(humVcc,LOW);
 int sen = 1023-val;
 int humT = ( sen /10);     //Se convierte la lectura del sensor en un porcentaje de 100-0%
 auxhum= humT;
 Serial.println("Sensor de humedad :");
 Serial.print(humT);
 Serial.print("%\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
 //Se declara la comunicacion de los sensores con arduino
  pinMode (humVcc,OUTPUT);
  digitalWrite(humPin,LOW);
  pinMode(rele, OUTPUT);
 
 while(!Serial);
 delay(1000);
 Serial.begin(9600); 
}

void loop() {
  digitalWrite(rele,LOW);
//SENSOR DE TEMPERATURA Y SUS RESPECTIVAS CONDICIONALES
  LM35();
  if(exttemp>60){
   digitalWrite (rele, HIGH);
  }
//SENSOR DE HUMEDAD Y SUS RESPECTIVAS CONDICIONALES 
  YL69();
  
  delay(1000);
}
