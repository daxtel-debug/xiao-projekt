#include <Arduino.h>.
// SÄNDARE: Seeed Studio XIAO (nRF52840 / SAMD21)
// Sparar ström med TPL5110 genom att klippa matningen via DONE-pinnen.

#include <DHT.h>
#include <RH_ASK.h> // Del av RadioHead-biblioteket
#include <SPI.h>    // Krävs av RadioHead

#define DHTPIN 2        // DHT22 ansluten till digital pinne D2
#define DHTTYPE DHT22
#define DONE_PIN 4      // TPL5110 DONE ansluten till digital pinne D4

DHT dht(DHTPIN, DHTTYPE);
// 2000 bps, RX-pinne används ej (0), TX-pinne på D3
RH_ASK driver(2000, 0, 3); 

void setup() {
  // Initiera hårdvara
  dht.begin();
  driver.init();
  
  // Kort väntetid så att DHT22-sensorn hinner stabilisera sin spänning
  delay(100); 
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Kontrollera att sensorn gav giltiga värden
  if (!isnan(humidity) && !isnan(temperature)) {
    char msg[32];
    // Formatera datan till en kompakt textsträng, t.ex. "T:21.5,H:48.3"
    snprintf(msg, sizeof(msg), "T:%.1f,H:%.1f", temperature, humidity);
    
    // Skicka paketet trådlöst
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
  }

  // --- AVSTÄNGNINGSMANÖVER ---
  // Säg till TPL5110 att sändningen är klar så att den klipper strömmen till batteriet!
  pinMode(DONE_PIN, OUTPUT);
  digitalWrite(DONE_PIN, HIGH); 
}

void loop() {}
