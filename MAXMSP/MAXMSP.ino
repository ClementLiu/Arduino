int sensor;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  sensor = analogRead(A0);
  // put your main code here, to run repeatedly:
Serial.write(sensor);
//Serial.println(sensor);
delay(100);
}
