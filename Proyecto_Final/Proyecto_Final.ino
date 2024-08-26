#include <SD.h>
#include <SPI.h>
#include <DHT.h>
#define SSpin 10


//MODULO SD
const int chipSelect = 10;

//SONIDO
int Mic = A0;
const int Umbral = 526;
int Valor;

//DT11
const int DHTPIN = 2;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

//LUZ
int Fotores = A5;
int Medicion;

File archivo;

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(Fotores, INPUT);


  if (!SD.begin(chipSelect)) { 
    Serial.println("Error al inicializar la tarjeta SD.");
    return;
  }

  Serial.println("Tarjeta SD inicializada.");
  archivo = SD.open("datos.txt", FILE_WRITE);
  if (!archivo) {
    Serial.println("Error al abrir el archivo.");
    return;
  }
}

void loop() {
  int Valor = analogRead(Mic);          
  float temp = dht.readTemperature(); 
  float humidity = dht.readHumidity();  
  Medicion = analogRead(Fotores);

  
  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Error al leer desde el sensor DHT.");
    return;
  }
  if (archivo) {
    archivo.print("Medicion de Sonido: ");
    archivo.println(Valor);
    archivo.print("Temperatura: ");
    archivo.print(temp);
    archivo.print("°C, Humedad: ");
    archivo.print(humidity);
    archivo.println("%");
    archivo.print("Medicion de Luz:");
    archivo.println(Medicion);
    archivo.close();  
    Serial.println("Datos guardados en datos.txt");
  } else {
    Serial.println("Error al abrir el archivo.");
  }
  //Monitor Serie
  Serial.print("Medicion de Sonido:   ");
  Serial.println(Valor);
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("°C  ");
  Serial.print(" Humedad: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Medicion de Luz:  ");
  Serial.println(Medicion);
  delay(5000);

  archivo.close();
  archivo = SD.open("datos.txt", FILE_WRITE); 
}
