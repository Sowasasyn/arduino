#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 6
int buzzer = 8;
int blue = 5;
int yellow = 4;
int red = 2;

MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(buzzer, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  digitalWrite(blue, HIGH);

  noTone(buzzer);
  Serial.println("Put your card to the reader...");
  Serial.println();
}
void loop() 
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print("Tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message: ");
  content.toUpperCase();
  if (content.substring(1) == "AA EF 64 29" ) 
  {
    Serial.println("Przyznano dostep");
    Serial.println();
    digitalWrite(red, HIGH);
    digitalWrite(blue, LOW);
    tone(buzzer, 1000);
    delay(50);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 1500);
    delay(50);
    noTone(buzzer);
    delay(3850);
    digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
  }
  else {
    Serial.println("Brak dostepu"); 
    Serial.println();
    digitalWrite(yellow, HIGH);
    digitalWrite(blue, LOW);
    tone(buzzer, 500);
    delay(50);
    noTone(buzzer);
    delay(50);
    tone(buzzer, 500);
    delay(50);
    noTone(buzzer);
    delay(3850);
    digitalWrite(yellow, LOW);
    digitalWrite(blue, HIGH);
  }
}