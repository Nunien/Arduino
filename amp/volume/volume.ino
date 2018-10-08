#define volumeSpeed 8
#define volumeDown 9
#define volumeUp 10

void setup() {
  // put your setup code here, to run once:
  pinMode(volumeSpeed, OUTPUT);
  pinMode(volumeDown, OUTPUT);
  pinMode(volumeUp, OUTPUT);
}


void loop() { 
  stopVolume(); 
  
  if (volumeDownPressed) {
    startVolumeLowering(255);
    delay(100);
    stopVolume(); 
  }
  if (volumeUpPressed) {
    startVolumeUpping(255);
    delay(100);
    stopVolume(); 
  }

}

void startVolumeLowering(int speed) {
  analogWrite(volumeSpeed, speed);
  digitalWrite(volumeDown, HIGH);
  digitalWrite(volumeUp, LOW);
}

void startVolumeUpping(int speed) {
  analogWrite(volumeSpeed, speed);
  digitalWrite(volumeDown, LOW);
  digitalWrite(volumeUp, HIGH);
}

void stopVolume() {
  digitalWrite(volumeDown, LOW);
  digitalWrite(volumeUp, LOW);
}

