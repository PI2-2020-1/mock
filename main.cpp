// CODE TO READ BME SENSOR AND SEND TO API SERVER VIA WIFI
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>         // to make requests
#include <Wire.h>
#include <Adafruit_Sensor.h>    // bme sensor
#include <Adafruit_BME280.h>    // bme sensor
#define SEALEVELPRESSURE_HPA (1013.25)

// wifi crerdentials
const char* ssid ="wifi_name";          //TODO
const char* password ="wifi_password";  //TODO

// variables
Adafruit_BME280 bme;
float temperature, humidity, pressure, altitude;
int time1 = 1;  // time in minutes
int time2;      // delay between requests

void setup() {
    Serial.begin(9600);
    Serial.println(F("BME280 test"));

    bool status;

    // default settings
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }

    Serial.println("-- Default Test --");
    time2 = time1*60*1000;

    Serial.println();
}

void connect_wifi(){
    Serial.println("");
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(10);
    }

    Serial.println("");
    Serial.println("Conectado com sucesso.");
    Serial.print("O IP é: ");
    Serial.println(WiFi.localIP());
}

void get_sensor_readings() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;                   //extra
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);        //extra
}


void loop() {
    Serial.println("Iniciando Loop");
    
    if (WiFi.status() != WL_CONNECTED) {
        connect_wifi();
    }

    get_sensor_readings();

    //String input = 
    // {
    //     "temp": "<temperature>",
    //     "hum": "<humidity>", 
    //     "pres": "<pressure>", 
    //     "alt": "<altitude>";
    // }
    // format -> \"name\":\"value\",
    String input = "{"
    input+="\"temp\":\"";
    input+=temperature;
    input+="\","
    input+="\"hum\":\"";
    input+=humidity;
    input+="\","
    input+="\"pres\":\"";
    input+=pressure;
    input+="\","
    input+="\"alt\":\"";
    input+=altitude;
    input+= "\"}";

    // POST, send data to API
    HTTPClient http;

    if(WiFi.status()== WL_CONNECTED){           //Check WiFi connection status
        http.begin("http://0.0.0.0:80/sics/");  //TODO

        http.addHeader("Content-Type", "application/json"); //Specify content-type header
        Serial.print("JSON: ");
        Serial.println(input);

        int httpResponseCode = http.POST(input); 

        if(httpResponseCode>0){
            String response = http.getString();  //Get the response to the request
            Serial.print("CODIGO: ");
            Serial.println(httpResponseCode);    //Print return code
            if (httpResponseCode == 201){
                Serial.println("Valores enviados com sucesso!");
            }
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
            Serial.println("");
            Serial.println("Desconectando");
            WiFi.disconnect();
            Conect_internet();
        }
        http.end();  //Free resources
    } else {
        Serial.println("Error na conexão WiFi");
        Serial.println("");
        Serial.println("Desconectando");
        WiFi.disconnect();
        connect_wifi();
    }

    delay(time2);  //Send a request every  minute
}

