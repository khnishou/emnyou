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
  roulerVerif_isSpace(1);
  delay(1000);
  roulerVerif_isNSpace(1);
  // roulerVerif_dist(30);

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

int roulerVerif_dist(float distanceCm)
{
  count_r = 0;
  count_l = 0;

  int cible = abs(distanceCm) / distParImpulsion;

  while (count_l < cible && count_r < cible)
  {
    if (!isSpace())
    {
      return (0);
    }
    if (count_l < cible)
      pulseServo(left10, (distanceCm > 0) ? 1700 : 1300);
    if (count_r < cible)
      pulseServo(right11, (distanceCm > 0) ? 1300 : 1700);
    delay(20);
  }
  return 1;
}

void roulerVerif_isNSpace(int direc)
{
  count_r = 0;
  count_l = 0;
  while (1)
  {
    if (!isSpace())
      break ;
    if (count_l <= count_r)
      pulseServo(left10, (direc > 0) ? 1700 : 1300);

    if (count_r <= count_l)
      pulseServo(right11, (direc > 0) ? 1300 : 1700);

    delay(20);
  }
}

void roulerVerif_isSpace(int direc)
{
  count_r = 0;
  count_l = 0;
  while (1)
  {
    if (isSpace())
      break ;
    if (count_l <= count_r)
      pulseServo(left10, (direc > 0) ? 1700 : 1300);

    if (count_r <= count_l)
      pulseServo(right11, (direc > 0) ? 1300 : 1700);

    delay(20);
  }
}

// void tournerSurLuiPrecis(int angle)
// {
//   count_r = 0;
//   count_l = 0;

//   int cible = (abs(angle) * 33.24) / (360 * distParImpulsion);

//   int varL = (angle > 0) ? 1700 : 1300;
//   int varR = (angle > 0) ? 1700 : 1300;

//   while (count_l < cible && count_r < cible) {
//     if (count_l < cible)
//       pulseServo(left10, varL);

//     if (count_r < cible)
//       pulseServo(right11, varR);

//     delay(20);
//   }
// }

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
