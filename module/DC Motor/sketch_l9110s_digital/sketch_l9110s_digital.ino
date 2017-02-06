
const int AIA = 4;
const int AIB = 7;

const int BIA = 9;
const int BIB = 10;

void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps
  Serial.println("L9110S digital example");

  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);
 stop();
 delay(2000);
}

void loop() {
  forward();
  delay(2000);
  stop();
  delay(2000);
  forward();
  delay(2000);
  stop();
  delay(2000);
  backward();
  delay(2000);
  stop();
  delay(2000);
  backward();
  delay(2000);
  stop();
  delay(2000);
}

void forward()
{
  Serial.println("forward");
  digitalWrite(AIA, HIGH);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, HIGH);
  digitalWrite(BIB, LOW);

}
void backward()
{
  Serial.println("backward");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, HIGH);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, HIGH);

}
void stop()
{
  Serial.println("stop");
  digitalWrite(AIA, LOW);
  digitalWrite(AIB, LOW);

  digitalWrite(BIA, LOW);
  digitalWrite(BIB, LOW);

}


