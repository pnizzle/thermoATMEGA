#define RLY1 22
#define RLY2 24
#define RLY3 26
#define DHTTYPE           DHT22     // DHT 22 (AM2302)
#define DHTPIN            39         // Pin which is connected to the DHT sensor.
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

int pinDHT22 = 39; //digital pin 39
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200); 
  // Initialize device.
  dht.begin();
  Serial.println("thermostat");
  // Print temperature sensor details.
  sensor_t sensor;

dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C"); 

 
 Serial.print("temperature"); Serial.print(" *C, ");
//Serial.print((float)humidity); Serial.println(" RH%");
  
  // DHT22 sampling rate is 0.5HZ.
  delayMS = sensor.min_delay / 1000;

pinMode(RLY1, OUTPUT);
pinMode(RLY2, OUTPUT);
pinMode(RLY3, OUTPUT);
digitalWrite(RLY1,LOW);
digitalWrite(RLY2,LOW);
digitalWrite(RLY3,LOW);
}
void loop() {
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print(" Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }

// AC on off with fan as rly2 and AC as rly1 need to add AC switch settings 
if ((event.temperature) >= 23.8){
  Serial.print("AC ON");
  digitalWrite(RLY1,HIGH);
  digitalWrite(RLY2,LOW);
  digitalWrite(RLY3,LOW);
  delay(30000);//set to 30000(30sec)
  digitalWrite(RLY1,HIGH);
  digitalWrite(RLY2,HIGH);
  digitalWrite(RLY3,LOW);
}
else{
  ((event.temperature) <= 22.00);
  Serial.print("AC OFF"); 
  digitalWrite(RLY1,LOW);
  digitalWrite(RLY2,LOW);
  digitalWrite(RLY3,LOW);
  delay(20000);
}
}
//heater function still needs work need to add heat switch setting 
//if((event.temperature) <= 23.8){
  //digitalWrite(RLY1,LOW);
 // digitalWrite(RLY2,HIGH);
 // digitalWrite(RLY3,LOW);
 // delay(1000);
 // Serial.print("heat on");
//}
//else {
 // digitalWrite(RLY1,LOW);
 // digitalWrite(RLY2,LOW);
 // digitalWrite(RLY3,LOW);  
//}
//}
