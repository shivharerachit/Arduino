int in1=34;
void setup() {
  Serial.begin(9600);
  pinMode(in1, INPUT);
}

void loop() {
  int ldr = analogRead(in1);
  Serial.print("LDR : ");
  Serial.println(ldr);
  delay(1000);
}
