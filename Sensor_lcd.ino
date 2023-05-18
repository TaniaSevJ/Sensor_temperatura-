#include <OneWire.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
Adafruit_SSD1306 display(-1); // <-- Ningun pin reiniciara la pantalla
#define ONE_WIRE_BUS 4 // <-- Se establece el pin 4 como bus OneWire
OneWire oneWire(ONE_WIRE_BUS); // <-- Protocolo de comunicacion por 1 cable
char buffer_temps[128];

const int lm35Pin = A0;  // Pin analógico al que está conectado el sensor LM35
const float temperaturaMaxima = 23.0;  // Temperatura máxima permitida para el foco

void setup() {  
  // No se necesitan declaran los pines analogicos
//ya que se realiza automáticamente
Serial.begin(9600);
 delay(100);
  Serial.println("Iniciando pantalla OLED");
    // Iniciar pantalla OLED en la dirección 0x3C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
#ifdef __DEBUG__
    Serial.println("No se encuentra la pantalla OLED");
#endif
    while (true);
  }
 }

void loop() {
//Se limpia la pantalla después de inicializarse 
  display.clearDisplay();
  
  int rawValue = analogRead(lm35Pin);  // Leer el valor analógico del sensor LM35
  float temperature = (rawValue * (50.0/1023.0));  // Calcular la temperatura en grados Celsius

  display.setTextColor(WHITE, BLACK); // <-- Pasa parametro de colores
  display.setTextSize(1); // <-- Tamaño de fuente 
  display.setCursor(0, 0); // <--Cordenadas para el cursor
  
  if (temperature >= temperaturaMaxima) {
    display.println("Temp: " + String(temperature)); // <-- Mostrar mensaje en pantalla
    display.println("Estado: Critico");
    display.display(); // <-- Transferencia de lo que se mostrara
    //Se limpiará la pantalla cada vez que cambie la numeración
    display.clearDisplay();
  } else {
    display.println("Temp: " + String(temperature)); // <-- Mostrar mensaje en pantalla
    display.println("Estado: Bueno");
    display.display(); // <-- Transferencia de lo que se mostrara
    //Se limpiará la pantalla cada vez que cambie la numeración
    display.clearDisplay();
  }
  
  delay(1000);  // Esperar 1 segundo antes de la siguiente lectura
}
