 /* 
  Connect 5V on Arduino to VCC on Relay Module
  Connect GND on Arduino to GND on Relay Module 
  Connect GND on Arduino to the Common Terminal (middle terminal) on Relay Module. */
 
#define AUX 7   // Connect Digital Pin 7 on Arduino to CH1 on Relay Module
 
void setup(){
  //Setup all the Arduino Pins
  pinMode(CH1, OUTPUT);
  
  //Turn OFF any power to the Relay channels
  digitalWrite(CH1,LOW);
  delay(2000); //Wait 2 seconds before starting sequence
}
 
void loop(){
  /*digitalWrite(CH1, HIGH);  //Green LED on, Yellow LED off
  delay(1000);
  digitalWrite(CH1, LOW);   //Yellow LED on, Green LED off
  delay(1000);*/
}
