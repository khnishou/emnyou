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
  tournerMoteur(distanceCm());
}

void pulseServo(int servoPin, int pulseLg)
{
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseLg);
  digitalWrite(servoPin, LOW);
}

void roulerPrecis(float direc)
{
  if (!direc)
  {
    pulseServo(left10, 1500);
    pulseServo(right11, 1500);
    delay(20);
    return ;
  }
  pulseServo(left10, (direc > 0) ? 1700 : 1300);
  pulseServo(right11, (direc > 0) ? 1300 : 1700);
  delay(20);
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

void tournerMoteur(float d)
{
  if (d > 17)
    roulerPrecis(1);
  else if (d < 13)
    roulerPrecis(-1);
  else
    roulerPrecis(0);
}
