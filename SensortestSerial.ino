// Inkluderer bibliotekene vi bruker
// DHT er til å bruke sensoren
#include "DHT.h"

// Definerer hvilken pin vi kobler sensoren til
#define DHTPIN A0

// Definerer hvilken type DHT-sensor vi bruker
#define DHTTYPE DHT11   // DHT 11

// Lager et dht-objekt som vi kan bruke til å lese data fra sensoren.
// dht-objektet ordner ting som å konvertere til enhetene vi bruker
// så vi slipper å lese inn voltstyrke manuelt
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Starter Serial monitor. Ikke nødvendig for å skrive til SD-kort
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  // Initialiser dht-sensor
  dht.begin();
}

void loop() {
  // Les inn luftfuktighet fra sensor
  float h = dht.readHumidity();

  // Les inn temperatur fra sensor (i Celsius)
  float t = dht.readTemperature();

  // Dersom noen av dem ikke klarte å lese inn: stopp koden
  // Dette vet programmet ved å sjekke om h eller t "isnan", dvs. is not a number
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 

  // Skriv data i følgende format: (h, t). Dette gjør det enkelt å lese inn i Python
  Serial.print("(");
  Serial.print(h);
  Serial.print(", ");
  Serial.print(t);
  Serial.println(")");

  // Vent noen sekunder mellom hver måling. Minimum er 2 sek (2000ms). her venter vi 2 sek
  delay(2000);
}
