String inputByte;
int BT_disconnectLed = 10;
int BT_StatePin = 11;

boolean BTconnected = false;
void setup() {

  pinMode(BT_StatePin, INPUT);
  pinMode(BT_disconnectLed, OUTPUT);
 
  Serial.begin(9600);
  Serial.println("Ready");
  Serial.println("Connect BT");

  
  while (!BTconnected) {
    if (digitalRead(BT_StatePin) == HIGH){BTconnected = true;};
    digitalWrite(BT_disconnectLed, HIGH); //Disconnected led indicate
    }

    digitalWrite(BT_disconnectLed, LOW);
    Serial.println("BT Connected Succesfully");
    Serial.print("");

  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

if (digitalRead(BT_StatePin) == LOW){BTconnected = false; digitalWrite(BT_disconnectLed, HIGH);}
if (digitalRead(BT_StatePin) == HIGH){BTconnected = true; digitalWrite(BT_disconnectLed, LOW);}

//command =[D1H0003600]
// unsigned long interval_in_ms = (min*60*1000)UL
while(Serial.available()>0){
    inputByte = Serial.readString();   //reading the bluetooth signal
  
    Serial.print("inputByte\t");
    Serial.println(inputByte);
    
    }


int commaIndex = inputByte.indexOf(',');

int secondCommaIndex = inputByte.indexOf(',', commaIndex + 1);

String signalValue = inputByte.substring(0,commaIndex);

long sgnlvalue = atol(signalValue);

String intervalValueInMin = inputByte.substring(commaIndex + 1);

unsigned long interval = intervalValueInMin.toInt();   //.toInt();

Serial.print("Signal Value");
Serial.println(signalValue);


Serial.print("intervalValueInMin");
Serial.println(intervalValueInMin);

    



}
