#include <Arduino.h>
#include <Wire.h>    // I2C
#include <HS300xlib.h>
#include <math.h>
#include "FS.h" // SD
#include "SD.h" // SD
#include <SPI.h> // Para SD
#include <DallasTemperature.h> // Para DS18B20
#include <OneWire.h> // Para DS18B20
#include <LiquidCrystal_I2C.h>
HS300xlib hs300x;  // create class

//------------------------------------------------------------------------------//
#define UPDATE_TIME 15000    // get data every 15 sec
#define SENSORADDRESS 0x07 // FS2012-1020-NG
#define SOUNDPIN 35 // Pin adc mic
#define ALFA 0.01 // filtrado media movil
#define SD_CS 5 //chip select del SD
#define ONE_WIRE_BUS 15 // Pin para DS18B20

uint32_t Counter = 0;

int SoundSensor = 0;
int SoundSensor_filtrado = 0;
int cantidad = 200;
float dB;

float Temperature0;
float Humidity0;
float Temperature1;
float Humidity1;
float Temperature2;
float Humidity2;
float Temperature3;
float Humidity3;
float Temperature4;
float Humidity4;
float TempContacto;
String dataMessage;

int lcdColumns = 20;
int lcdRows = 4;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); 
//------------------------------------------------------------------------------//

//---------------------------------------------------------//
// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1 = { 0x28, 0xFE, 0xB5, 0x75, 0xD0, 0x1, 0x3C, 0xB };
//---------------------------------------------------------//

//---------------------------------------------------------//
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  //Serial.println(bus);
}
//--------------------------------------------------------//

//--------------------------------------------------------//
// Initialize SD card
void initSDCard(){
   SD.begin(SD_CS);
   if (!SD.begin()) {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Card Mount Failed.");
    delay(2000);
    lcd.clear();
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("No SD card attached.");
    delay(2000);
    lcd.clear();
    return;
  }
}
//--------------------------------------------------------//

//--------------------------------------------------------//
// Write to the SD card
void writeFile(fs::FS &fs, const char * path, const char * message) {

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Failed to writing.");
    delay(2000);
    lcd.clear();
    return;
  }
  if(file.print(message)) {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("File written");
    delay(2000);
    lcd.clear();
    
  } else {
    lcd.clear();
    lcd.setCursor(4,0);    
    lcd.print("Write failed");
    delay(2000);
    lcd.clear();
  }
  file.close();
}
//--------------------------------------------------------//

//--------------------------------------------------------//
// Append data to the SD card 
void appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    lcd.clear();
    lcd.setCursor(0,0);       
    lcd.print("Failed to appending.");
    delay(2000);
    lcd.clear();
    return;
  }
  if(file.print(message)) {
    lcd.clear();
    lcd.setCursor(2,0);        
    lcd.print("Message appended");
    delay(2000);
    lcd.clear();
    
  } 
  else {
    lcd.clear();
    lcd.setCursor(3,0);       
    lcd.print("Append failed.");
    delay(2000);
    lcd.clear(); 
  }
  file.close();
}
//--------------------------------------------------------//

void setup(){
  Serial.begin(115200);
  pinMode(SOUNDPIN,INPUT);
  Wire.begin(); // inicia I2C
  lcd.begin();
  lcd.backlight();    
  lcd.setCursor(5,1);
  lcd.print("INCUB TEST");
  delay(3000);
  lcd.clear();
  initSDCard();
  sensors.begin(); //ds18b20
 
//--------------------------------------------------------//
  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/data.csv");
  if(!file) {
    lcd.clear();
    lcd.setCursor (1, 0);
    lcd.print("File doesn't exist");
    lcd.setCursor(2,1);
    lcd.print("Creating file...");
    delay(2000);
    writeFile(SD, "/data.csv", "Temperature0, Humidity0, Temperature1, Humidity1, Temperature2, Humidity2, Temperature3, Humidity3, Temperature4, Humidity4, Temp Contacto, Sonido, Flujo \r\n");
    lcd.clear();
  }
  
  else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("File already exists.");
    delay(2000);
    appendFile(SD, "/data.csv", "Temperature0, Humidity0, Temperature1, Humidity1, Temperature2, Humidity2, Temperature3, Humidity3, Temperature4, Humidity4, Temp Contacto, Sonido, Flujo \r\n");
    lcd.clear();
  }
  file.close();   
//--------------------------------------------------------//   
      
}

void loop(){
  // contador para tomar muestras cada X tiempo
  uint32_t now = millis();
  if (now - Counter > UPDATE_TIME) {
    
//--------------------------------------------------------// Hay que tomar varias muestras y promediar... Terminar de calibrar...
//  Sensor de sonido nuevo
      int mediciones [cantidad];
      int acumulador = 0;
      float promedio = 0;     
      
      for (int i=0; i<cantidad; i++)
      {
        SoundSensor = analogRead(SOUNDPIN);
        SoundSensor_filtrado = (ALFA*SoundSensor) + ((1-ALFA)*SoundSensor_filtrado);
        mediciones[i] = SoundSensor_filtrado;
        delay(10);
      }
      
      for (int i=0; i<cantidad; i++) {
        acumulador += mediciones [i];
      }
      
      promedio = acumulador / cantidad;
      dB = -0.0633*promedio + 91.404;
//--------------------------------------------------------//

//--------------------------------------------------------// 
// Tomar lecturas del ds18b20
    sensors.requestTemperatures(); // Send the command to get temperatures
    TempContacto = sensors.getTempC(sensor1);
//--------------------------------------------------------// 
    
    TCA9548A(0);
    int8_t respon0 = hs300x.MeasurementReq();
    if(respon0){
        Humidity0 = hs300x.getHumidity();
        Temperature0 = hs300x.getTemperatureC();
    }

    TCA9548A(1);
    int8_t respon1 = hs300x.MeasurementReq();
    if(respon1){
        Humidity1 = hs300x.getHumidity();
        Temperature1 = hs300x.getTemperatureC();
    }

    TCA9548A(2);
    int8_t respon2 = hs300x.MeasurementReq();
    if(respon2){
        Humidity2 = hs300x.getHumidity();
        Temperature2 = hs300x.getTemperatureC();
    }

    TCA9548A(3);
    int8_t respon3 = hs300x.MeasurementReq();
    if(respon3){
        Humidity3 = hs300x.getHumidity();
        Temperature3 = hs300x.getTemperatureC();
    }

    TCA9548A(4);
    int8_t respon4 = hs300x.MeasurementReq();
    if(respon4){
        Humidity4 = hs300x.getHumidity();
        Temperature4 = hs300x.getTemperatureC();
    }

//--------------------------------------------------------//
// lecturas del sensor de flujo
    TCA9548A(5);
    Wire.beginTransmission(SENSORADDRESS);
    Wire.write(1);
    Wire.endTransmission();
    delay (20);
    
    Wire.requestFrom(SENSORADDRESS, 2);
    while(Wire.available() == 0);
    byte a = Wire.read(); // first received byte stored here ....Example bytes one: 00011001 10000000
    byte b = Wire.read(); // second received byte stored here ....Example bytes two: 11100111 00000000
  
    float flow =  ((a << 8) + b);
//--------------------------------------------------------// 

//--------------------------------------------------------// 
//cargar datos a tarjeta SD
    //Concatenate all info separated by commas
    dataMessage = String(Temperature0) + "," + String(Humidity0) + "," + String(Temperature1) + "," + String(Humidity1) + "," + String(Temperature2) + "," + String(Humidity2) + "," + String(Temperature3) + "," + String(Humidity3) + "," + String(Temperature4) + "," + String(Humidity4) + "," + String(TempContacto) + "," + String(dB) + "," + String(flow) + "\r\n";
    lcd.clear();  
    lcd.setCursor(4,0);  
    lcd.print("Saving data.");
    delay(2000);
    appendFile(SD, "/data.csv", dataMessage.c_str());
    lcd.clear();
//--------------------------------------------------------//    
 
//--------------------------------------------------------//  
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T1:");
    lcd.setCursor(3,0);
    lcd.print(Temperature1);
    lcd.setCursor(8,0);
    lcd.print("C");
    
    lcd.setCursor(11, 0);
    lcd.print("Tc:"); 
    lcd.setCursor(14,0);
    lcd.print(TempContacto); 
    lcd.setCursor(19,0);
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print("T2:"); 
    lcd.setCursor(3,1);  
    lcd.print(Temperature2);
    lcd.setCursor(8,1);   
    lcd.print("C");
    
    lcd.setCursor(11, 1);
    lcd.print("H0:"); 
    lcd.setCursor(14,1);  
    lcd.print(Humidity0); 
    lcd.setCursor(19,1);  
    lcd.print("%");  
    
    lcd.setCursor(0, 2);
    lcd.print("T3:"); 
    lcd.setCursor(3,2);    
    lcd.print(Temperature3); 
    lcd.setCursor(8,2);     
    lcd.print("C");
    
    lcd.setCursor(11, 2);  
    lcd.print("N:"); 
    lcd.setCursor(13,2);    
    lcd.print(dB); 
    lcd.setCursor(18,2);    
    lcd.print("dB");
    
    lcd.setCursor(0, 3);
    lcd.print("T4:"); 
    lcd.setCursor(3,3);      
    lcd.print(Temperature4); 
    lcd.setCursor(8,3);     
    lcd.print("C");
    
    lcd.setCursor(11, 3);
    lcd.print("F:"); 
    lcd.setCursor(13, 3);  
    lcd.print(flow); 
    lcd.setCursor(17, 3);    
    lcd.print("mLm");
//--------------------------------------------------------// 

  Counter = now;
  }
}
