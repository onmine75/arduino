const float baseline = 0.80;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float vol;
  int sensorValue = analogRead(A0);
  vol = (float)sensorValue / 1024.0 * 5.0;
  Serial.print("sensor=");
  Serial.print(sensorValue);
  Serial.print(", ");
  Serial.print(vol, 2);
  Serial.print(", ");
  if (vol > (baseline + 2.5)) {
    Serial.print("You are a beer. 5/5 Level");
  } else if (vol > (baseline + 2.0)) {
    Serial.print("You must have drunk. 4/5 Level");
  } else if (vol > (baseline + 1.5)) {
    Serial.print("You must have drunk. 3/5 Level");
  } else if (vol > (baseline + 1.0)) {
    Serial.print("You seem to have drunk. 2/5 Level");
  } else if (vol > (baseline + 0.5)) {
    Serial.print("You seem to have drunk. 1/5 Level");
  } else
  {
    Serial.print("Alcohol is not detect!!");
  }
  Serial.println("");
}
