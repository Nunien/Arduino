#include <IRremote.h>

#define volumeSpeedPin 8
#define volumeDownPin 10
#define volumeUpPin 9

#define volumeUpIRCode 0x490
#define volumeDownIRCode 0xC90
#define buttonHoldIRCode 0xFFFFFF

#define max32Bits 2147483647
#define volumeCycleTime 200


int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long lastIRCode = 0x0;
unsigned long lastIRTime = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Initialise le recepteur

  pinMode(volumeSpeedPin, OUTPUT);
  pinMode(volumeDownPin, OUTPUT);
  pinMode(volumeUpPin, OUTPUT);
}

void loop() {
  
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    if (results.value == volumeDownIRCode) {
      Serial.println("volume down");
      startVolumeLowering(255);
      lastIRTime = millis();
    } 
    
    else if (results.value == volumeUpIRCode) {
      Serial.println("volume up");
      startVolumeUpping(255);
      lastIRTime = millis();
    }

    else if (results.value == buttonHoldIRCode) {
      Serial.println("continue");
      if (lastIRCode == volumeDownIRCode || lastIRCode == volumeUpIRCode) {
        lastIRTime = millis();
      }
    } 
    
    lastIRCode = results.value;
    irrecv.resume(); // Recoit la valeur suivante
  }

  if ((millis()-lastIRTime)%max32Bits > volumeCycleTime) {
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
