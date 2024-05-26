//SENSOR DE TEMPERATURA DHT11
#include <DHT.h>    //Libreria sensor DHT11
#include <DHT_U.h>  //Libreria sensor DHT11
float SENSOR = 4;   //Pin Digital 4
float TEMPERATURA;  
int HUMEDAD;
DHT dht(SENSOR, DHT11);  //Objeto DHT con pin conectado en la salida digital 4

//SENSOR DE CALIDAD DEL AIRE
int MQ135 = 0  //Pin analogico A2
int AIRE;
int CO2;
int GAS;

//SENSOR DE SONIDO
int KY08 = 2;  //Pin digital 2
int VALORKY08;          


//SENSOR DE LUMINOSIDAD
int FOTORESISTENCIA = A5; //Pin analogico A5
int VALORF;

void setup() {

  Serial.begin(9600);  //Incializacion del puerto serie

  //SENSOR DE TEMPERATURA DHT11
  dht.begin();  // Inicializacion del sensor DHT11

  //SENSOR DE CALIDAD DEL AIRE
  digitalWrite(AIRE, LOW); //Declaramos la variable AIRE como estado bajo 
  digitalWrite(CO2, LOW);  //Declaramos la variable CO2 como estado bajo
  digitalWrite(GAS, LOW);  //Declaramos la variable GAS como estado bajo
  //SENSOR DE SONIDO
  pinMode(KY08, INPUT);
  //SENSOR DE LUMINOSIDAD
  pinMode(FOTORESISTENCIA, INPUT);
}

void loop() {
  //SENSOR DE TEMPERATURA DHT11
  TEMPERATURA = dht.readTemperature();  // Lee el Valor de Temperatura
  HUMEDAD = dht.readHumidity();         //Lee el Valor de Humedad
  Serial.print("TEMPERATURA: ");
  Serial.print(TEMPERATURA);  //Imprimir en el monitor serie el valor de Temperatura
  Serial.print("°C HUMEDAD: ");
  Serial.print(HUMEDAD);  //Imprimir en el monitor serie el valor de Humedad
  Serial.println("%");
  delay(1000);
  //SENSOR DE CALIDAD DEL AIRE
  MQ135 = analogRead(0);     //Lee el valor analogico del sensor 
  Serial.print(MQ135, DEC);  //Muestra el valor en decimal 
  Serial.print("ppm");
  delay(250);
  //aire
  if (MQ135 <= 55) {
    Serial.print("Aire normal");  //Valor menor o igual a 55  aire normal
    delay(50);
  }
  //aire con dioxido humano
  if (MQ135 >= 56 && MQ135 <= 65) { //Valor mayor o igual a 56 y menor o igual a 65 aire con un poco de CO2
    Serial.print("Aire con un poco de CO2");
    delay(50);
  }
  //dioxido de carbono
  if (MQ135 >= 74 && MQ135 <= 350) { //Valor mayor o igual a 74 y menor o igual a 350 dioxido de CO2
    Serial.print("Dioxido de CO2");
    delay(50);
  }
  //Gas propano y butano
  if (MQ135 >= 400) {  //Valor mayor o igual a 400 propano o butano 
    Serial.print("Propano / butano");
  }
  //SENSOR DE SONIDO
  VALORKY08 = digitalRead(Microfono);  //Lee el valor del sensor y lo guarda en VALORKY08

  //SENSOR DE LUMUNOSIDAD
  VALORF = analogRead(FOTORESISTENCIA); //Lee el valor del sensor y lo guarda en VALORF
  Serial.println(VALORF); 
}