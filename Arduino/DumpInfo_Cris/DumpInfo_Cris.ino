//CP4 2TDSJ
//Cristine Acocella RM88251
//Jonathan Felix RM88082


#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

/////Json
#include <ArduinoJson.h>
const int TAMANHO = 50;
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   
Servo myServo;
 
void setup() 
{
  Serial.begin(9600);  
  Serial.setTimeout(10);
  SPI.begin();      
  mfrc522.PCD_Init();
  myServo.attach(8);
  myServo.write(0);
  delay(1000);
  myServo.write(180);
 
}
 
void loop() 
{
  StaticJsonDocument<TAMANHO> json; 
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  

  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  conteudo.toUpperCase();
    //formato de escrita do json
  json["card"] = conteudo;
  json["msg"] = " ";
  json["aut"] = false;

  serializeJson(json, Serial);
  Serial.println();
  
  delay(1000);

while (Serial.available() > 0) {
    StaticJsonDocument<200> json2;
    deserializeJson(json2, Serial);
    if(json2.containsKey("aut")) {
      myServo.write(0);
      delay(1000);
      myServo.write(180);
    }
  } 
  
  delay(1000);

} 
