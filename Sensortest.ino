// Inkluderer bibliotekene vi bruker
// SPI og SD er til å bruke SD-kortet
// DHT er til å bruke sensoren
#include <SPI.h>
#include <SD.h>
#include "DHT.h"

// Definerer hvilken pin vi kobler sensoren til
#define DHTPIN A0

// Definerer hvilken type DHT-sensor vi bruker
#define DHTTYPE DHT11   // DHT 11

// Lager et dht-objekt som vi kan bruke til å lese data fra sensoren.
// dht-objektet ordner ting som å konvertere til enhetene vi bruker
// så vi slipper å lese inn voltstyrke manuelt
DHT dht(DHTPIN, DHTTYPE);

// Lager et fil-objekt som vi kan bruke til å skrive data til filer på SD-kortet
File file;

void setup() {
  // Starter Serial monitor. Ikke nødvendig for å skrive til SD-kort
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  // Start SD-kort biblioteket. Hvis den ikke får startet (hvis det ikke er noe SD-kort), bare stopp programmet
  if(!SD.begin(4)) {
    Serial.println("Feiled");
    return;
  }

  // Åpne filen vi skal skrive dataen til. Dersom filen ikke eksisterer vil den lage en ny fil med det navnet
  // Åpne i FILE_WRITE, dvs. skrivemodus (kontra lesemodus)
  file = SD.open("data.txt", FILE_WRITE);

  // Skriv en linje med følgende overskrift. Dette så vi kan skille måling-sessions fra hverandre
  file.println("Temperature and humidity measurements");

  // Lukk filen for at teksten skal bli skrevet til filen
  file.close();

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

  // Igjen, åpne fil for å skrive data
  file = SD.open("data.txt", FILE_WRITE);

  // Skriv data i følgende format: (h, t). Dette gjør det enkelt å lese inn i Python
  file.print("(");
  file.print(h);
  file.print(", ");
  file.print(t);
  file.println(")");

  // Lukk filen for å lagre dataen
  file.close();

  // Vent noen sekunder mellom hver måling. Minimum er 2 sek (2000ms). her venter vi 20 sek
  delay(20000);
}
