#include <SD.h>
#include <SPI.h>
#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
const unsigned long delayt = 5000;

// MODULO RTC
RTC_DS3231 rtc;

// MODULO SD
const int CS = 10;

// SENSOR DE SONIDO KY-038
const int PinMic = A0;
const float Vbase = 1.0;
float ValorMic;

// DHT11
const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

// LDR
const int PinLdr = A3;

//Funciones:

//Conversión de voltaje a dB
float calcularDb() {
  ValorMic = analogRead(PinMic);
  float voltaje = ValorMic * (5.0 / 1023.0);

  if (voltaje > 0) {
    return 20 * log10(voltaje / Vbase);
  } else {
    Serial.println("Voltaje demasiado bajo para calcular dB.");
    return -1;
  }
}
  // Conversión de ADC a voltaje
  float adc_a_voltaje(int valorADC) {
    const float Vref = 5.0;
    return (valorADC / 1023.0) * Vref;
  }

  // Conversión de voltaje a lux
  float voltaje_a_lux(float voltaje) {
    const float m = 100.0;  // Pendiente
    const float b = 0.0;    // Intersección
    return (m * voltaje) + b;
  }

  File archivo;

  void setup() {
    Serial.begin(9600);
    dht.begin();

    if (!rtc.begin()) {
      Serial.println("Modulo RTC no Encontrado");
      while (1);
    }

    if (!SD.begin(CS)) {
      Serial.println("Error al inicializar la tarjeta SD.");
      return;
    }

    Serial.println("Tarjeta SD inicializada.");
  }

  void loop() {
   DateTime fecha = rtc.now();
  // Imprimir fecha y hora
  Serial.print(fecha.day());
  Serial.print("/");
  Serial.print(fecha.month());
  Serial.print("/");
  Serial.print(fecha.year());
  Serial.print(" ");
  
  //  Ceros a la izquierda
  if (fecha.hour() < 10) Serial.print("0");
  Serial.print(fecha.hour());
  Serial.print(":");
  
  if (fecha.minute() < 10) Serial.print("0");
  Serial.print(fecha.minute());
  Serial.print(":");
  
  if (fecha.second() < 10) Serial.print("0");
  Serial.println(fecha.second());

    // Lecturas de sensores
    float dB = calcularDb();
    delay(1000);
    float temp = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temp) || isnan(humidity)) {
      Serial.println("Error al leer desde el sensor DHT.");
      return;
    }
    float ldr_value = analogRead(PinLdr);
    float voltaje = adc_a_voltaje(ldr_value);
    float lux = voltaje_a_lux(voltaje);



    //Guardado de Lecturas de Sensores
    archivo = SD.open("SENSORES.txt", FILE_WRITE);
    if (archivo) {
      //Documentar fecha y hora en el archivo
      archivo.print(fecha.day());
      archivo.print("/");
      archivo.print(fecha.month());
      archivo.print("/");
      archivo.print(fecha.year());
      archivo.print(" ");

      //Añadir ceros a la izquierda en la hora
      if (fecha.hour() < 10) archivo.print("0");
      archivo.print(fecha.hour());
      archivo.print(":");

      if (fecha.minute() < 10) archivo.print("0");
      archivo.print(fecha.minute());
      archivo.print(":");

      if (fecha.second() < 10) archivo.print("0");
      archivo.print(fecha.second());
      archivo.println();

      //Imprimir valores de sensores
      archivo.print("Nivel de sonido: ");
      archivo.print(dB);
      archivo.println(" dB");
      archivo.print("Temperatura: ");
      archivo.print(temp);
      archivo.print("°C, Humedad: ");
      archivo.print(humidity);
      archivo.println("%");
      archivo.print("Nivel de Intensidad de luz: ");
      archivo.print(lux);
      archivo.println(" lx");
      archivo.println();
      archivo.close();
    } else {
      Serial.println("Error al abrir el archivo.");
    }
  
  
  // Monitor Serie
  Serial.print("Nivel de sonido: ");
  Serial.print(dB);
  Serial.println(" dB");
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("°C  ");
  Serial.print(" Humedad: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Nivel de Intensidad de luz: ");
  Serial.print(lux);
  Serial.println(" lx");
  Serial.println();
  
  delay(delayt);
}

