int left10 = 10;
int right11 = 11;

int pingPin = 7;
float v = 331.5+0.6*20;

int headPin = 12;

volatile int count_r = 0;
volatile int count_l = 0;

const float distParImpulsion = 0.325;

void roue_r()
{
  count_r++;
}

void roue_l()
{
  count_l++;
}

void setup()
{
  pinMode(servoPin, OUTPUT);
  pinMode(left10, OUTPUT);
  pinMode(right11, OUTPUT);

  pinMode(sensorLeftPin, INPUT_PULLUP);
  pinMode(sensorRightPin, INPUT_PULLUP);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), roue_r, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), roue_l, CHANGE);

  randomSeed(analogRead(A0));
}

void loop()
{

  roulerPrecis(100);
  delay(500);
}

void pulseServo(int servoPin, int pulseLg)
{
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLg);
  digitalWrite(servoPin, LOW);
}

void roulerPrecis(float distanceCm)
{

  count_r = 0;
  count_l = 0;
  int count = 0;

  int cible = abs(distanceCm) / distParImpulsion;

  while (count_l < cible && count_r < cible)
  {
    if (count_l < cible)
      pulseServo(left10, (distanceCm > 0) ? 1700 : 1300);

    if (count_r < cible)
      pulseServo(right11, (distanceCm > 0) ? 1300 : 1700);

    delay(20);
  }
}

void tournerSurLuiPrecis(int angle)
{
  count_r = 0;
  count_l = 0;

  int cible = (abs(angle) * 33.24) / (360 * distParImpulsion);

  int varL = (angle > 0) ? 1700 : 1300;
  int varR = (angle > 0) ? 1700 : 1300;

  while (count_l < cible && count_r < cible) {
    if (count_l < cible)
      pulseServo(left10, varL);

    if (count_r < cible)
      pulseServo(right11, varR);

    delay(20);
  }
}

float microsecondsToCentimeters(float microseconds) {
  return microseconds / 58;
}

float distanceCm()
{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(pingPin, INPUT);
  float duration = pulseIn(pingPin, HIGH);
  float t = duration /29.0/2 ;
  float d = v*t ;
  cm = microsecondsToCentimeters(duration);

  return cm; 
} 

void tournerMoteur(float d)
{
  if (d > 32)
    roulerPrecis(5)
  else if (d < 28)
    roulerPrecis(-5)
  else
    roulerPrecis(0)
}