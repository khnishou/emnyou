int left10 = 10;
int right11 = 11;

int pingPin = 7;
float v = 331.5+0.6*20;

int headPin = 12;

volatile int count_r = 0;
volatile int count_l = 0;

const float distParImpulsion = 0.325;
int target = 40 / distParImpulsion;

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
  pinMode(pingPin, OUTPUT);
  pinMode(left10, OUTPUT);
  pinMode(right11, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), roue_r, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), roue_l, CHANGE);

  randomSeed(analogRead(A0));
}

void loop()
{
  rouler_isSpace(1);
  delay(1000);
  rouler_isNSpace(1);
  if (count_r >= target || count_l >= target)
  {
    tournerSurRouePrecis(-45,right11);
    roulerPrecis(-15);
    tournerSurRouePrecis(-45,left10);
    
    delay(5000000000) ;
  }
  delay(1000);

}

int isSpace()
{
  return (distanceCm() > 15);
}

void pulseServo(int servoPin, int pulseLg)
{
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLg);
  digitalWrite(servoPin, LOW);
}

void rouler_isNSpace(int direc)
{
  count_r = 0;
  count_l = 0;
  
  while (count_r < target && count_l < target)
  {
    if (!isSpace())
      break ;
    pulseServo(left10, (direc > 0) ? 1700 : 1300);
    pulseServo(right11, (direc > 0) ? 1300 : 1700);

    delay(20);
  }
  Serial.println(count_r);
  Serial.println(count_l);

}

void rouler_isSpace(int direc)
{
  count_r = 0;
  count_l = 0;
  while (1)
  {
    if (isSpace())
      break ;
    pulseServo(left10, (direc > 0) ? 1700 : 1300);
    pulseServo(right11, (direc > 0) ? 1300 : 1700);

    delay(20);
  }
}

void roulerPrecis(float distanceCm)
{

  count_r = 0;
  count_l = 0;

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

  return microsecondsToCentimeters(duration); 
} 

void tournerSurRouePrecis(int angle, int roue) {
  count_r = 0;
  count_l = 0;

  int cible = (abs(angle) * 66.48) / (360 * distParImpulsion);

  while ((roue == left10 && count_r < cible) ||
         (roue == right11 && count_l < cible)) {

    if (roue == left10)
      pulseServo(right11, (angle > 0) ? 1300 : 1700);
    else if (roue == right11)
      pulseServo(left10, (angle > 0) ? 1700 : 1300);

    delay(20);
  }
}
