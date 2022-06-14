#define TempPin A1
#define HumPin A0 
#define GasPin A3 
#define LEDGreenPin 3 
#define LEDRedPin 4 
#define BuzzerPin 5 
#define HumanPresencePin 7 
#define LightPin 12 
#define FanPin 13 

String gasMessage, humanPresenceMessage, lightMessage, fanMessage;
//int light, smoke, pir;
String light, smoke, pir;

 
void setup() {
  //INPUT
   pinMode(HumanPresencePin, INPUT);
   pinMode(GasPin, INPUT);
   pinMode(TempPin, INPUT);
   pinMode(HumPin, INPUT);
   
  //OUTPUT
   pinMode(LEDGreenPin, OUTPUT); 
   pinMode(LEDRedPin, OUTPUT); 
   pinMode(BuzzerPin, OUTPUT); 
   pinMode(LightPin, OUTPUT);
   pinMode(FanPin, OUTPUT);

   Serial.begin(9600);

}

void loop(){
    delay(200); 

    int humanPresence = digitalRead(HumanPresencePin); 
    int gas = digitalRead(GasPin);
 
    float tempAnalog = analogRead(TempPin);
    float temperature = (tempAnalog/1024.0)*500; 
    float humAnalog = analogRead(HumPin);
    float humidity = (((humAnalog/1024.0)-0.1515)/0.00636)/(1.0546-0.00216*temperature); 

    if(isnan(humanPresence) || isnan(gas) || isnan(temperature) || isnan (humidity)){
      Serial.println(F("The system could not able to read from sensor"));
       return;
    }

    if (humanPresence == LOW) { 
     humanPresenceMessage = "There is no human in room."; 
     lightMessage = "Light is off.";
     fanMessage = "Fan is off."; 
     //pir=0;
     pir = "No";
 
     digitalWrite(LEDGreenPin, LOW); 
     digitalWrite(LEDRedPin, HIGH );  
     digitalWrite(LightPin, LOW);
     digitalWrite(FanPin, LOW); 
     
   }
   else {
    
      humanPresenceMessage = "Human is present.";
      lightMessage = "Light is on."; 
      //pir =1;
       pir = "Yes";
 
      digitalWrite(LEDGreenPin, HIGH);
      digitalWrite(LEDRedPin, LOW);
      digitalWrite(LightPin, HIGH);  

      if (temperature >= 25){
        fanMessage = "Fan is on."; 
        digitalWrite(FanPin, HIGH); 
      } 
      else {
          fanMessage = "Fan is Off."; 
          digitalWrite(FanPin, LOW);
      }

   }

   if (gas == HIGH) {
     gasMessage = "Smoke Detected. Fire Alert!"; 
     //smoke = 1;
     smoke = "Yes";


     tone(BuzzerPin, 200); 
     delay(20); 
     noTone(BuzzerPin); 
   } 
   else{
     gasMessage  = "No smoke detected."; 
     //smoke = 0;
     smoke = "No";
   }

  Serial.println(humanPresenceMessage); 
  Serial.println(lightMessage); 
  Serial.println("Temperature: "+String(temperature));
  Serial.println(fanMessage);
  Serial.println("Humidity: "+String(humidity));

 
  if (humidity >70)
     Serial.println("WARNING: Humidity exceeded normal condition!"); 
  else
     Serial.println("Humidity is in normal condition."); 

 Serial.println(gasMessage); 

// Serial.println(temperature); 
 //Serial.println(smoke); 
 //Serial.println(humidity);
 //Serial.println(pir);
 
  Serial.println();
}
