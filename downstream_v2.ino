#define GREEN_1 20
#define RED_1 19
#define GREEN_2 17
#define RED_2 16
#define GREEN_3 14
#define RED_3 13
#define INA 4
#define INB 5


byte speed = 80; // change this to alter fan speed 0 - 255 although 80 is the minimum for reliable operation
unsigned int capacity=3;//parking slots

void setup() { 
  // Setup serial for monitor and Setup Serial1 for BlueTooth
  Serial.begin(9600);  
  Serial1.begin(9600); 
  pinMode(INA,OUTPUT);
  pinMode(INB,OUTPUT);

  pinMode(GREEN_1, OUTPUT);
  pinMode(RED_1, OUTPUT);
  pinMode(GREEN_2, OUTPUT);
  pinMode(RED_2, OUTPUT);
  pinMode(GREEN_3, OUTPUT);
  pinMode(RED_3, OUTPUT);
}

void loop() {
  if(Serial1.available() > 0){
    String str = Serial1.readStringUntil('@');     
    //Serial.println(str); 
    if(str.startsWith("speed")){
      speed=str.substring(6).toInt();
      //Serial.println(speed);    
    }
    else{
      int green;
      int red;
      if(str.substring(4,5)=='1'){
        green=GREEN_1;
        red=RED_1;
      }
      else if(str.substring(4,5)=='2'){
        green=GREEN_2;
        red=RED_2;
      }
      else if(str.substring(4,5)=='3'){
        green=GREEN_3;
        red=RED_3;
      }
      if(str.substring(6)=="Green"){
        digitalWrite(green,HIGH);
        digitalWrite(red,LOW);
      }
      else if (str.substring(6)=="Red"){
        digitalWrite(green,LOW);
        digitalWrite(red,HIGH);
      }
    }
    analogWrite(INA,0);
    analogWrite(INB,speed);    
  }    
}
