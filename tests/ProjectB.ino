int left10 = 10;
int right11 = 11;

int sensorLeftPin = 5;
int sensorRightPin = 6;

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
    if (distanceCm > 0)
      count = wallCheck(count);
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

bool wallLeft()
{
  return digitalRead(sensorLeftPin) == HIGH;
}

bool wallRight()
{
  return digitalRead(sensorRightPin) == HIGH;
}

void demiTour(int angle, int direction, int back)
{
  roulerPrecis(-(back));
  tournerSurLuiPrecis(angle * direction);
}

int wallCheck(int count)
{
  int angle;
  
  

  if (!wallLeft() || !wallRight())
  {
    if (count > 3)
    {
      angle = random(100, 180);
      count = 0;
    }
    else
      angle = random(30, 80);
    delay(500);
    if (!wallLeft() && !wallRight())
    {
      Serial.println("FFFFFFFF");
      demiTour(225, 1, 10);
      return (count);
    }
    if (!wallLeft()) {
      Serial.println("LLLLLLLL");
      demiTour(angle, 1, 5);
      return (count + 1);
    }
    if (!wallRight()) {
      Serial.println("RRRRRRR");
      demiTour(angle, -1, 5);
      return (count + 1);
    }
  }
  return (count);
}