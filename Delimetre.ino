String inputByte;
const int BT_disconnectLed = 10;
const int BT_StatePin = 11;
boolean BTconnected = false;

char lamp_state = '0';
const int relay_port = 12;
const int ledpin = 10;

String sgnlvalue;
unsigned long intervalInMs;

unsigned long interval;
unsigned long lampTurnedOnAt;
unsigned long lampTurnedOffAt;

unsigned long time_for_action;

unsigned long buttonPushedMillis;
unsigned long receivedTime;



void setup() {

  pinMode(BT_StatePin, INPUT);
  pinMode(BT_disconnectLed, OUTPUT);

  pinMode(relay_port, OUTPUT);
  digitalWrite(relay_port , HIGH); //relay off
  
 
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

}



void loop() {
unsigned long currentMillis = millis();

if (digitalRead(BT_StatePin) == LOW){BTconnected = false; digitalWrite(BT_disconnectLed, HIGH);}
if (digitalRead(BT_StatePin) == HIGH){BTconnected = true; digitalWrite(BT_disconnectLed, LOW);}

//command =[D1H, 3600]

while(Serial.available()>0){
    inputByte = Serial.readString();   //reading the bluetooth signal
  
    Serial.print("input\t");
    Serial.println(inputByte);
    


int openingBraceIndex = inputByte.indexOf('[');
int commaIndex = inputByte.indexOf(',', openingBraceIndex + 1);
int secondCommaIndex = inputByte.indexOf(',', commaIndex + 1);
int closingBraceIndex = inputByte.indexOf(']',openingBraceIndex + 1);

String signalValue = inputByte.substring(openingBraceIndex+1,commaIndex);
String sgnlvalue = signalValue;
//       signalValue = "";
String intervalValueInSec = inputByte.substring(commaIndex + 1, closingBraceIndex);

intervalInMs = strtoul(intervalValueInSec.c_str(), NULL, 10) * 1000UL;

if(sgnlvalue == "DCH"){
  buttonPushedMillis = currentMillis;
  }


Serial.print("Signal Value ");


Serial.println(signalValue);

Serial.print("Sgnl value ");
Serial.println(sgnlvalue);



Serial.print("intervalValueInMiliSec ");
Serial.println(intervalInMs);


Serial.print("intervalValueInSec ");
Serial.println(interval);

}


if(sgnlvalue == "DCH"){
      digitalWrite(relay_port, LOW);

//      unsigned long duration = currentMillis-buttonPushedMillis;
      lampTurnedOnAt = currentMillis;
      Serial.println("LampOn");

      
if((unsigned long)(currentMillis - buttonPushedMillis) > (unsigned long) intervalInMs ){

        digitalWrite(relay_port, HIGH);
        Serial.println("Lamp off");
              
        lamp_state = '0';
        Serial.print("Lamp State--->\t");
        Serial.println(lamp_state);
//        
//        lampTurnedOffAt = currentMillis;
//        
        Serial.print("currentMillis \t");
        Serial.println(currentMillis);

        Serial.print(" buttonPushedMillis\t");
        Serial.println(buttonPushedMillis);
  }


      
      Serial.print("lampTurnedOnAt\t");
      Serial.println(lampTurnedOnAt);
      
      lamp_state = '1';
      Serial.print("Lamp State--->\t");
      Serial.println(lamp_state);
      
       sgnlvalue= "";
}

if(sgnlvalue == "DCL"){

digitalWrite(relay_port, HIGH);
lamp_state = '0';
Serial.println("Lamp off");
Serial.print("Lamp State-->\t");
Serial.println(lamp_state);

sgnlvalue = "";

}




//Serial.print("Sgnl Value after on ");
//Serial.println(sgnlvalue);
//
//
//Serial.print("intervalValueInMiliSec after ");
//Serial.println(intervalInMs);
//
//
//Serial.print("intervalValueInSec after ");
//Serial.println(interval);



 
if (BTconnected == false) {
   Serial.print("BT Disconnected\t");
   digitalWrite(relay_port, HIGH);
    Serial.println("Lamp off");
//    digitalWrite(ledpin, HIGH);


    
};

sgnlvalue = "";


}
