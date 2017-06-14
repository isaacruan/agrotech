//SENSOR DE TEMPERATURA
int tempC;
int lecTemp;
int temPin = A9;
int x=0;  //variable que almacena la lectura de temperatura
int g=0;  //variable que almacena la humedad
int f=0; //variable que almacena la temperatura convertida a centigrados 
const int rele = 52;

//SENSOR DE HUMEDAD
byte humPin = A8;
byte humVcc = 33;
//////////////////////////////////////////////////////////////////////
void LM35(){
 lecTemp = analogRead(temPin);
 tempC = lecTemp/9.31;
 x=lecTemp;
 f = tempC;
 Serial.println("Sensor de temperatura :");
 Serial.print(lecTemp);
 Serial.print(" C\n");
}
//////////////////////////////////////////////////////////////////////
void YL69(){
 digitalWrite(humVcc, HIGH);
 delay(500);
 int val = analogRead(humPin);
 digitalWrite(humVcc,LOW);
 int sen = 1023-val;
 int humT = ( sen /10);
 g = humT;
 Serial.println("Sensor de humedad :");
 Serial.print(humT);
 Serial.print("%\n");
}
//////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  //analogReference(INTERNAL);
  
 //SENSOR DE HUMEDAD
  pinMode (humVcc,OUTPUT);
  digitalWrite(humPin,LOW);
  pinMode(8,OUTPUT);
  pinMode(10,OUTPUT);
 
 while(!Serial);
 delay(1000);
 pinMode(rele, OUTPUT);
 Serial.begin(9600); 
}

void loop() {
  digitalWrite(8,LOW);
  digitalWrite(10,LOW);
  digitalWrite(rele,LOW);
//SENSOR DE TEMPERATURA
  LM35();
  if(f<=30){
    digitalWrite(10,HIGH);
  }
  if(x>60){
   digitalWrite (rele, HIGH);
  }
//SENSOR DE HUMEDAD
  YL69();
  if (g>=40){
  digitalWrite(8,HIGH);
  }
  delay(1000);
}
