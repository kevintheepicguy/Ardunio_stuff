int calibrationTime = 30;
//the time when the sensor outputs a low impulse
long unsigned int lowIn;
//the amount of milliseconds the sensor has to be low
//before we assume all motion has stopped
long unsigned int pause = 30;
boolean lockLow = true;
boolean takeLowTime;
int pirPin = 3;    //the digital pin connected to the PIR sensor's output
int ledPin = 6;
////
//SETUP
void setup(){
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(pirPin, LOW);
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
  }
//LOOP
void loop(){
  if(digitalRead(pirPin) == HIGH){
      digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
      if(lockLow){
      lockLow = false;
      Serial.println("---");
      Serial.print("motion detected at ");
      Serial.print(millis()/1000);
      Serial.println(" sec");
      digitalWrite(ledPin, HIGH);
      delay(50);
      }
      takeLowTime = true;
  }
  if(digitalRead(pirPin) == LOW){
      //digitalWrite(ledPin, LOW);  //the led visualizes the sensors output pin state
      if(takeLowTime){
          lowIn = millis();          //save the time of the transition from high to LOW
          takeLowTime = false;       
      }
      //if the sensor is low for more than the given pause,
         //a new motion sequence has been detected
          lockLow = true;
          Serial.print("motion ended at ");      //output
          Serial.print((millis() - pause)/1000);
          Serial.println(" sec");
          delay(50);
            //we assume that no more motion is going to happen
      if(!lockLow && millis() - lowIn > pause){
          //makes sure this block of code is only executed again after
  }
  }
}
