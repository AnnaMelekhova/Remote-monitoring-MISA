#include <Wire.h>
#include <SparkFun_APDS9960.h>
#include "Pipeline.h"
#include "Classifier.h"

SparkFun_APDS9960 apds = SparkFun_APDS9960();
uint16_t ambient_light = 0;
uint16_t red_light = 0;
uint16_t green_light = 0;
uint16_t blue_light = 0;
uint8_t proximity_data = 0;


void setup()
{
  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println(F("--------------------------------"));
  Serial.println(F("SparkFun APDS-9960 - ColorSensor"));
  Serial.println(F("--------------------------------"));
  
  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Start running the APDS-9960 light sensor (no interrupts)
  if ( apds.enableLightSensor(false) ) {
    Serial.println(F("Light sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during light sensor init!"));
  }
  if ( apds.init() ) {
    Serial.println(F("APDS-9960 initialization complete"));
  } else {
    Serial.println(F("Something went wrong during APDS-9960 init!"));
  }
  
  // Adjust the Proximity sensor gain
  if ( !apds.setProximityGain(PGAIN_2X) ) {
    Serial.println(F("Something went wrong trying to set PGAIN"));
  }
  
  // Start running the APDS-9960 proximity sensor (no interrupts)
  if ( apds.enableProximitySensor(false) ) {
    Serial.println(F("Proximity sensor is now running"));
  } else {
    Serial.println(F("Something went wrong during sensor init!"));
  }
  // Wait for initialization and calibration to finish
  delay(500);
}

void loop()
{

float a = apds.readAmbientLight(ambient_light);
float r = (float)apds.readRedLight(red_light) / 65535.0 * 3.4028235E+38;
//float r = apds.readRedLight(red_light);
float g = apds.readGreenLight(green_light);
float b = apds.readBlueLight(blue_light);
float prox = apds.readProximity(proximity_data);



float features[] = {apds.readAmbientLight(ambient_light),r,g,b};
    
  if (!pipeline.transform(features))
      return;

 
  Serial.print(apds.readAmbientLight(ambient_light));
  Serial.print(",");
  Serial.print("RGB: ");
  Serial.print(r,3);
  Serial.print(",");
  Serial.print(g,3);
  Serial.print(",");
  Serial.print(b,3);

  // perform classification on pipeline result
  Serial.print(" |  Predicted color: ");
  Serial.println(tree.predict(pipeline.X));
   delay(1000);
}