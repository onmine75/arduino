
const int AIA = 5;  // PWM
const int AIB = 6;  // PWM

const int BIA = 9;  // PWM
const int BIB = 10;  // PWM

byte speed = 255;  // change this (0-255) to control the speed of the motors

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("L9110S example");

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
 stop();
 delay(2000);
}

void loop() {
  forward(255);
  delay(2000);
  stop();
  delay(2000);
  forward(155);
  delay(2000);
  stop();
  delay(2000);
  backward(255);
  delay(2000);
  stop();
  delay(2000);
  backward(155);
  delay(2000);
  stop();
  delay(2000);
}

void forward(byte speed)
{
  Serial.print("forward speed=");
  Serial.println(speed);
  analogWrite(AIA, speed);
  digitalWrite(AIB, LOW);

  analogWrite(BIA, speed);
  digitalWrite(BIB, LOW);

}
void backward(byte speed)
{
  Serial.print("backward speed=");
  Serial.println(speed);
  digitalWrite(AIA, LOW);
  analogWrite(AIB, speed);

  digitalWrite(BIA, LOW);
  analogWrite(BIB, speed);

}
void stop()
{
  Serial.println("stop");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);

}


