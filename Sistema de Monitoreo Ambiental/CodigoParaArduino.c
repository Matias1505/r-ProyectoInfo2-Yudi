#include <DHT.h>
#include <SD.h>
#include <SPI.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define LDR_PIN A0
#define SOUND_SENSOR_PIN A1
#define MQ135_PIN A2
#define SD_CS_PIN 10

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    dht.begin();

    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Error initializing SD card");
        return;
    }
}

void loop() {
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightLevel = analogRead(LDR_PIN);
    int soundLevel = analogRead(SOUND_SENSOR_PIN);
    int airQuality = analogRead(MQ135_PIN);

    if (isnan(temp) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    String dataString = "Temp: " + String(temp) + "C, " +
                        "Humidity: " + String(humidity) + "%, " +
                        "Light Level: " + String(lightLevel) + ", " +
                        "Sound Level: " + String(soundLevel) + ", " +
                        "Air Quality: " + String(airQuality);

    Serial.println(dataString);

    File dataFile = SD.open("data.txt", FILE_WRITE);
    if (dataFile) {
        dataFile.println(dataString);
        dataFile.close();
    } else {
        Serial.println("Error opening data file");
    }

    delay(2000);  // Espera 2 segundos entre lecturas
}