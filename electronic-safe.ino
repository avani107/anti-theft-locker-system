#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

#define SERVO_PIN 6
#define GREEN_LED A4
#define RED_LED   A5
#define BUZZER    13

#define LOCK_POSITION   20
#define UNLOCK_POSITION 90

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {A3, A2, A1, A0};

Keypad keypad = Keypad(
  makeKeymap(keys),
  rowPins,
  colPins,
  ROWS,
  COLS
);

Servo lockServo;

const String CORRECT_PASSWORD = "1234";
String enteredPassword = "";
int failedAttempts = 0;
const int MAX_ATTEMPTS = 3;
bool alarmActive = false;

void setup()
{
  Serial.begin(9600);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  lockServo.attach(SERVO_PIN);
  lockServo.write(LOCK_POSITION);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ANTI-THEFT");
  lcd.setCursor(0, 1);
  lcd.print("LOCKER SYSTEM");

  Serial.println("================================");
  Serial.println("    ANTI-THEFT LOCKER SYSTEM");
  Serial.println("================================");
  Serial.println("System Started");
  Serial.println("Locker Status: LOCKED");

  delay(2000);
  showEnterPassword();
}

void loop()
{
  if (alarmActive) return;

  char key = keypad.getKey();
  if (key) handleKeyPress(key);
}

void handleKeyPress(char key)
{
  if (key == '#')
  {
    checkPassword();
  }
  else if (key == '*')
  {
    enteredPassword = "";
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PASSWORD CLEAR");
    Serial.println("Password cleared.");
    delay(1000);
    showEnterPassword();
  }
  else if (key >= '0' && key <= '9')
  {
    if (enteredPassword.length() < 8)
    {
      enteredPassword += key;
      lcd.setCursor(0, 1);
      for (int i = 0; i < enteredPassword.length(); i++) lcd.print("*");
      Serial.print("*");
    }
  }
}

void checkPassword()
{
  Serial.println();
  Serial.println("Checking password...");

  if (enteredPassword == CORRECT_PASSWORD)
    accessGranted();
  else
    accessDenied();

  enteredPassword = "";
}

void accessGranted()
{
  failedAttempts = 0;
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  Serial.println("ACCESS GRANTED");
  Serial.println("Correct password.");
  Serial.println("Unlocking locker...");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACCESS GRANTED");
  lcd.setCursor(0, 1);
  lcd.print("LOCKER OPEN");

  lockServo.write(UNLOCK_POSITION);
  delay(5000);
  autoLock();
}

void accessDenied()
{
  failedAttempts++;
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  Serial.println("ACCESS DENIED");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ACCESS DENIED");
  lcd.setCursor(0, 1);
  lcd.print("ATTEMPT: ");
  lcd.print(failedAttempts);
  lcd.print("/");
  lcd.print(MAX_ATTEMPTS);

  delay(1500);

  if (failedAttempts >= MAX_ATTEMPTS)
    activateAlarm();
  else
  {
    digitalWrite(RED_LED, LOW);
    showEnterPassword();
  }
}

void activateAlarm()
{
  alarmActive = true;
  digitalWrite(RED_LED, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("!!! ALERT !!!");
  lcd.setCursor(0, 1);
  lcd.print("LOCKER LOCKED");

  Serial.println();
  Serial.println("============================");
  Serial.println("      SECURITY ALERT");
  Serial.println("   THREE FAILED ATTEMPTS");
  Serial.println("    LOCKER REMAINS LOCKED");
  Serial.println("============================");

  for (int i = 0; i < 10; i++)
  {
    digitalWrite(BUZZER, HIGH);
    delay(200);
    digitalWrite(BUZZER, LOW);
    delay(200);
  }

  digitalWrite(RED_LED, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM LOCKED");
  lcd.setCursor(0, 1);
  lcd.print("RESET REQUIRED");

  Serial.println("Alarm completed.");
  Serial.println("Reset Arduino to restart.");
}

void autoLock()
{
  lockServo.write(LOCK_POSITION);
  digitalWrite(GREEN_LED, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AUTO LOCKED");
  lcd.setCursor(0, 1);
  lcd.print("SAFE");

  Serial.println("Locker automatically locked.");
  delay(2000);
  showEnterPassword();
}

void showEnterPassword()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ENTER PASSWORD:");
  lcd.setCursor(0, 1);

  Serial.println();
  Serial.println("Locker is LOCKED.");
  Serial.println("Enter password and press #.");
  Serial.println("Press * to clear.");
}
