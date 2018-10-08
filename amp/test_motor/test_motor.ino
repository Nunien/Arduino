#define enA 8
#define in1 9
#define in2 10

void setup() {
  // put your setup code here, to run once:
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}


void loop() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set speed to 200 out of possible range 0~255
  analogWrite(enA, 255);

  delay(10000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  

  delay(10000);
}
