# 1 "F:\\SEMESTER\\Fall- 21\\CSE360\\LAB\\Final Project\\ArduinoCode\\Finalproject\\Final\\Final.ino"
# 11 "F:\\SEMESTER\\Fall- 21\\CSE360\\LAB\\Final Project\\ArduinoCode\\Finalproject\\Final\\Final.ino"
String gasMessage, humanPresenceMessage, lightMessage, fanMessage;
int light, smoke, pir;
//String light, smoke, pir;


void setup() {
  //INPUT
   pinMode(7, 0x0);
   pinMode(A3, 0x0);
   pinMode(A1, 0x0);
   pinMode(A0, 0x0);

  //OUTPUT
   pinMode(3, 0x1);
   pinMode(4, 0x1);
   pinMode(5, 0x1);
   pinMode(12, 0x1);
   pinMode(13, 0x1);

   Serial.begin(9600);

}

void loop(){
    delay(200);

    int humanPresence = digitalRead(7);
    int gas = digitalRead(A3);

    float tempAnalog = analogRead(A1);
    float temperature = (tempAnalog/1024.0)*500;
    float humAnalog = analogRead(A0);
    float humidity = (((humAnalog/1024.0)-0.1515)/0.00636)/(1.0546-0.00216*temperature);

    if(isnan(humanPresence) || isnan(gas) || isnan(temperature) || isnan (humidity)){
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 46 "F:\\SEMESTER\\Fall- 21\\CSE360\\LAB\\Final Project\\ArduinoCode\\Finalproject\\Final\\Final.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 46 "F:\\SEMESTER\\Fall- 21\\CSE360\\LAB\\Final Project\\ArduinoCode\\Finalproject\\Final\\Final.ino"
                    "The system could not able to read from sensor"
# 46 "F:\\SEMESTER\\Fall- 21\\CSE360\\LAB\\Final Project\\ArduinoCode\\Finalproject\\Final\\Final.ino" 3
                    ); &__c[0];}))
# 46 "F:\\SEMESTER\\Fall- 21\\CSE360\\LAB\\Final Project\\ArduinoCode\\Finalproject\\Final\\Final.ino"
                    )));
       return;
    }

    if (humanPresence == 0x0) {
     humanPresenceMessage = "There is no human in room.";
     lightMessage = "Light is off.";
     fanMessage = "Fan is off.";
     pir=0;
     //pir = "No";

     digitalWrite(3, 0x0);
     digitalWrite(4, 0x1 );
     digitalWrite(12, 0x0);
     digitalWrite(13, 0x0);

   }
   else {

      humanPresenceMessage = "Human is present.";
      lightMessage = "Light is on.";
      pir =1;
      //pir = "Yes";

      digitalWrite(3, 0x1);
      digitalWrite(4, 0x0);
      digitalWrite(12, 0x1);

      if (temperature >= 25){
        fanMessage = "Fan is on.";
        digitalWrite(13, 0x1);
      }
      else {
          fanMessage = "Fan is Off.";
          digitalWrite(13, 0x0);
      }

   }

   if (gas == 0x1) {
     gasMessage = "Smoke Detected. Fire Alert!";
     smoke = 1;
     //smoke = "Yes";


     tone(5,200);
     //delay(20); 
     noTone(5);
   }
   else{
     gasMessage = "No smoke detected.";
     smoke = 0;
     //smoke = "No";
   }

  //Serial.println(humanPresenceMessage); 
  //Serial.println(lightMessage); 
  //Serial.println("Temperature: "+String(temperature));
  //Serial.println(fanMessage);
  //Serial.println("Humidity: "+String(humidity));


  //if (humidity >70)
     //Serial.println("WARNING: Humidity exceeded normal condition!"); 
  //else
     //Serial.println("Humidity is in normal condition."); 

 //Serial.println(gasMessage); 

 Serial.println(temperature);
 Serial.println(smoke);
 Serial.println(humidity);
 Serial.println(pir);

 Serial.println();
}
