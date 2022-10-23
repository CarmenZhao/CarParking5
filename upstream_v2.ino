#include <NewPing.h>
#include <MQ135.h>

#define TRIGGER_I 14
#define ECHO_I 13
#define TRIGGER_II 17
#define ECHO_II 16
#define TRIGGER_III 20
#define ECHO_III 19
#define MAX_DISTANCE 10
#define MQ135_AO_PIN 12

float MQ135_AOvalue;
unsigned int Distance_I;
unsigned int Distance_II;
unsigned int Distance_III; 

bool isEmpty_I=true;
bool isEmpty_II=true;
bool isEmpty_III=true;

//set diff intervals for reading sensors
long previousMill_MQ135 = 0;    
long previousMill_Distance = 0;

long MQ135_Interval = 3000; 
long Distance_Interval = 1000;    
unsigned long currentMillis = 0;

// NewPing setup of pins and maximum distance
NewPing sonar_I(TRIGGER_I, ECHO_I, MAX_DISTANCE); 
NewPing sonar_II(TRIGGER_II, ECHO_II, MAX_DISTANCE); 
NewPing sonar_III(TRIGGER_III, ECHO_III, MAX_DISTANCE); 

MQ135 mq135_sensor(MQ135_AO_PIN);
 
void setup() {
   Serial.begin(9600);
   Serial1.begin(9600); 
   currentMillis = millis();
}
 
void loop() {
 // capture the current time
  currentMillis = millis();
  readSonar();
  readMQ135();
}

void readMQ135(){
  if(currentMillis - previousMill_MQ135 > MQ135_Interval) {
    //store the time of this change   
    previousMill_MQ135 = currentMillis;
    float rzero = mq135_sensor.getRZero();
    float ppm = mq135_sensor.getPPM();
   Serial.print("RZero:");
   Serial.println(rzero);
   Serial1.print("Air Quality:");
   Serial1.println(ppm);
  } 
}

void readSonar(){
  if(currentMillis - previousMill_Distance > Distance_Interval) {
    //store the time of this change
    bool temp_I;
    bool temp_II;
    bool temp_III;   
    previousMill_Distance = currentMillis;
    Distance_I = sonar_I.ping_cm();
    if(Distance_I>0){
      temp_I=false;
    }
    else{
      temp_I=true;
    }
    if(temp_I!=isEmpty_I){
      isEmpty_I=temp_I;
      Serial.print("Distance_I:");
      Serial.println(Distance_I);
      Serial1.print("slot1:");
      Serial1.println(isEmpty_I);
    }
    Distance_II = sonar_II.ping_cm();
    if(Distance_II>0){
      temp_II=false;
    }
    else{
      temp_II=true;
    }
    if(temp_II!=isEmpty_II){
      isEmpty_II=temp_II;
      Serial.print("Distance_II:");
      Serial.println(Distance_II);
      Serial1.print("slot2:");
      Serial1.println(isEmpty_II);
    }
    Distance_III = sonar_III.ping_cm();
    if(Distance_III>0){
      temp_III=false;
    }
    else{
      temp_III=true;
    }
    if(temp_III!=isEmpty_III){
      isEmpty_III=temp_III;
      Serial.print("Distance_III:");
      Serial.println(Distance_III);
      Serial1.print("slot3:");
      Serial1.println(isEmpty_III);  
    }
  }
}
