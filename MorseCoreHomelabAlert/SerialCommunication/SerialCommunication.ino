int x;

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1);
  Serial.println("Systems ready");
}

void loop() {
  while (!Serial.available());
  x=Serial.readString().toInt();
  Serial.print(x+1);
}
