#define LED 3
#define button 2
volatile int buttonState;

#define buzzer 6

#include <Servo.h>
Servo myservo;
#define SERVO_PIN 9

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 7

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define PHOTOS  A0
int max_lux = 0;
int angle_lux = 0;
volatile int value = 0;
void setup()
{
  Serial.begin(9600);
  pinMode(button, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo.attach(SERVO_PIN);
  lcd.init();
}

void loop ()
{
    buttonState = digitalRead(button);
    if (buttonState == 0)
    {
        super_complex_code();
    }
    else
    {
       main_code();
    }
    delay(100);
}

void main_code()
{
    int chk;
    volatile int curr_lux = 0;
    for (int i = 0; i < 180; i++)
    {
        myservo.write(i);
        delay(20);
        if (!(i % 45))
        {
            curr_lux = analogRead(PHOTOS);
            Serial.println(curr_lux);
            if (curr_lux > max_lux)
            {
                max_lux = curr_lux;
                angle = i;
                digitalWrite(led, HIGH);
                good_song();
                digitalWrite(led, LOW);
            }
            else
                bad_song();
        }
    }
    for (int i = 180; i > 0; i--)
    {
        myservo.write(i);
        delay(20);
    }
    for (int i = 0; i < angle; i++)
    {
        myservo.write(i);
        delay(20);
    }
    chk = DHT.read(DHT11_PIN);
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("hum: ");
    lcd.print(String(DHT.humidity));
    lcd.setCursor(0, 1);
    lcd.print("tmp: ");
    lcd.print(String(DHT.temperature));
    delay(5000);
}

void super_complex_code()
{
   for (int i = 0; i < 2; i++) 
   {
      tone(buzzer, 440); 
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494); 
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 587);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494); 
      delay(200);
      noTone(buzzer);
      delay(50);
  
      tone(buzzer, 740); 
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 740);  
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 659);  
      delay(800);
      noTone(buzzer);
      delay(100);
  
      tone(buzzer, 440);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 587);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494);  
      delay(200);
      noTone(buzzer);
      delay(50);
  
      tone(buzzer, 659); 
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 659);  
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 587);  
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 554);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494);  
      delay(400);
      noTone(buzzer);
      delay(100);
  
      tone(buzzer, 440);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 587);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494);  
      delay(200);
      noTone(buzzer);
      delay(50);
  
      tone(buzzer, 587);  
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 554);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 494);  
      delay(200);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 440);  
      delay(400);
      noTone(buzzer);
      delay(50);
  
      tone(buzzer, 659);  
      delay(400);
      noTone(buzzer);
      delay(50);
      tone(buzzer, 587);  
      delay(800);
      noTone(buzzer);
      
      delay(500);
    }
}

void good_song()
{
 tone(buzzer, 659);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 494);  
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 587);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 494);
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 440); 
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 440);  
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 659); 
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 587); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523);
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 494); 
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 494);  
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 587);
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 659);
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 440);
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 440);  
  delay(600);
  noTone(buzzer);
  delay(100);


  tone(buzzer, 587);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 698);  
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 880);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 784);
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 698);
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 659); 
  delay(600);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 659); 
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 587);
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523); 
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 494);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 494);  
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523);  
  delay(200);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 587);
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 659);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 523);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 440);  
  delay(450);
  noTone(buzzer);
  delay(50);

  tone(buzzer, 440);  
  delay(600);
  noTone(buzzer);
}



void bad_song()
{
  digitalWrite(led, HIGH);
  tone(buzzer, 392); delay(560);
  digitalWrite(led, LOW);
  noTone(buzzer); delay(60);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 392); delay(560);
  digitalWrite(led, LOW);
  noTone(buzzer); delay(60);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 392); delay(560);
  digitalWrite(led, LOW);
  noTone(buzzer); delay(60);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 311); delay(440);
  
  digitalWrite(led, LOW);
  tone(buzzer, 466); delay(190);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 392); delay(625);
  
  digitalWrite(led, LOW);
  tone(buzzer, 311); delay(440);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 466); delay(190);
  
  digitalWrite(led, LOW);
  tone(buzzer, 392); delay(1250);
  
  // Deuxième partie
  digitalWrite(led, HIGH);
  tone(buzzer, 587); delay(560);
  digitalWrite(led, LOW);
  noTone(buzzer); delay(60);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 587); delay(560);
  digitalWrite(led, LOW);
  noTone(buzzer); delay(60);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 587); delay(560);
  digitalWrite(led, LOW);
  noTone(buzzer); delay(60);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 622); delay(440);
  
  digitalWrite(led, LOW);
  tone(buzzer, 466); delay(190);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 370); delay(625);
  
  digitalWrite(led, LOW);
  tone(buzzer, 311); delay(440);
  
  digitalWrite(led, HIGH);
  tone(buzzer, 466); delay(190);
  
  digitalWrite(led, LOW);
  tone(buzzer, 392); delay(1250);
  
  noTone(buzzer);
  digitalWrite(led, LOW);
}
