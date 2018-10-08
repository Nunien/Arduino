#include <IRremote.h>

#define volumeSpeedPin 8
#define volumeDownPin 10
#define volumeUpPin 9
#define irReceiverPin 11
#define sourceLeftPin 12  // Connected to CLK on KY-040
#define sourceRightPin 13  // Connected to DT on KY-040
#define analog1 14
#define analog2 15
#define analog3 16
#define dacOut 17
#define digital1 4
#define digital2 5
#define digital3 6
#define digital4 7

#define volumeUpIRCode 0x490
#define volumeDownIRCode 0xC90
#define channelUpIRCode 0x90
#define channelDownIRCode 0x890
#define buttonHoldIRCode 0xFFFFFFFF

#define max32Bits 2147483647
#define volumeCycleTime 50
#define channelCycleTime 50

// IR
IRrecv irrecv(irReceiverPin);
decode_results results;
unsigned long lastIRCode = 0x0;
unsigned long lastIRTimeVolume = 0;
unsigned long lastIRTimeChannel = 0;

// Source encodeur
int pinALast;  
int aVal;
boolean bCW;

int currentChannel;
int channels[7][2] = {{analog1}, {analog2}, {analog3}, {digital1, dacOut}, {digital2, dacOut}, {digital3, dacOut}, {digital4, dacOut}};

void setup()
{
  Serial.begin(9600);
  
  irrecv.enableIRIn(); // Init IR receiver

  pinMode(volumeSpeedPin, OUTPUT);
  pinMode(volumeDownPin, OUTPUT);
  pinMode(volumeUpPin, OUTPUT);

  pinMode (sourceLeftPin,INPUT);
  pinMode (sourceRightPin,INPUT);
  pinALast = digitalRead(sourceLeftPin);

  pinMode(analog1, OUTPUT);
  pinMode(analog2, OUTPUT);
  pinMode(analog3, OUTPUT);
  pinMode(dacOut, OUTPUT);
  pinMode(digital1, OUTPUT);
  pinMode(digital2, OUTPUT);
  pinMode(digital3, OUTPUT);
  pinMode(digital4, OUTPUT);

  digitalWrite(analog1, LOW);
  digitalWrite(analog2, HIGH);
  digitalWrite(analog3, HIGH);
  digitalWrite(dacOut, HIGH);
  digitalWrite(digital1, HIGH);
  digitalWrite(digital2, HIGH);
  digitalWrite(digital3, HIGH);
  digitalWrite(digital4, HIGH);

  currentChannel = 0;

  delay(2000);
}

void loop() {
  processIR();
  processSourceEncoder();
}

void processSourceEncoder() {
  aVal = digitalRead(sourceLeftPin);
  if (aVal != pinALast){ // Means the knob is rotating
   // if the knob is rotating, we need to determine direction
   // We do that by reading pin B.
   if (digitalRead(sourceRightPin) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
     Serial.println ("clockwise");
     channelUp();
   } else {// Otherwise B changed first and we're moving CCW
     Serial.println("counterclockwise");
     channelDown();
   }
   delay(10);
  } 
  pinALast = digitalRead(sourceLeftPin);
}

void processIR() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == volumeDownIRCode) {
      Serial.println("IR volume down");
      startVolumeLowering(255);
      lastIRTimeVolume = millis();
    } 
    
    else if (results.value == volumeUpIRCode) {
      Serial.println("IR volume up");
      startVolumeUpping(255);
      lastIRTimeVolume = millis();
    }

    else if (results.value == channelUpIRCode) {
      Serial.println("IR channel up");
      if (modulo((millis()-lastIRTimeChannel), max32Bits) > channelCycleTime) {
        channelUp();
      }
      lastIRTimeChannel = millis();
    }

    else if (results.value == channelDownIRCode) {
      Serial.println("IR channel down");
      if (modulo((millis()-lastIRTimeChannel), max32Bits) > channelCycleTime) {
        channelDown();
      }
      lastIRTimeChannel = millis();
    }

    else if (results.value == buttonHoldIRCode) {
      Serial.println("IR continue");
      if (lastIRCode == volumeDownIRCode || lastIRCode == volumeUpIRCode) {
        lastIRTimeVolume = millis();
      }
      if (lastIRCode == channelDownIRCode || lastIRCode == channelUpIRCode) {
        lastIRTimeChannel = millis();
      }
    } 

    lastIRCode = results.value;
    irrecv.resume(); // Recoit la valeur suivante
  }

  if (modulo((millis()-lastIRTimeVolume), max32Bits) > volumeCycleTime) {
    stopVolume();
  }
}

void startVolumeLowering(int speed) {
  analogWrite(volumeSpeedPin, speed);
  digitalWrite(volumeDownPin, HIGH);
  digitalWrite(volumeUpPin, LOW);
}

void startVolumeUpping(int speed) {
  analogWrite(volumeSpeedPin, speed);
  digitalWrite(volumeDownPin, LOW);
  digitalWrite(volumeUpPin, HIGH);
}

void stopVolume() {
  digitalWrite(volumeDownPin, LOW);
  digitalWrite(volumeUpPin, LOW);
}

void channelUp() {
 Serial.println("channel up at ------------------------------------"); 
 Serial.println(millis()); 
 switchChannel(modulo((currentChannel+1), 7));
}  

void channelDown() {
 Serial.println("channel down at ------------------------------------"); 
 Serial.println(millis()); 
 switchChannel(modulo((currentChannel-1),7));
}

void switchChannel(int to) {
  int from = currentChannel;
  Serial.println("switch channel from " + String(from) + " to " + String(to) ); 
  for(int i=0; i<2; i++) {
    digitalWrite(channels[from][i], HIGH);
  }
  for(int i=0; i<2; i++) {
    digitalWrite(channels[to][i], LOW);
  }
  currentChannel = to; 
}

long modulo (long val, unsigned long mod) {
    return (val + mod * ((long)abs(floor(val / (long)mod))+1)) % mod;
}

