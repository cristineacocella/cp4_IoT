

/////Json
#include <ArduinoJson.h>
const int TAMANHO = 50;  

///// Sensor DTH
#include "DHT.h"
#define DHTPIN  7 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE); 

void setup() 
{
  //inicialia c sensor
  dht.begin();

  //inicializa comunicação serial
  Serial.begin(9600);
}

void loop() 
{
  StaticJsonDocument<TAMANHO> json;

  // Faz a leitura da temperatura  
  float temp = dht.readTemperature();
  // faz a leitura da humidade
  float umi = dht.readHumidity();

  //formato de escrita do json
  json["temperatura"] = temp;
  json["umidade"] = umi;

  serializeJson(json, Serial);
  Serial.println();

  //delay
  delay(500);
}
