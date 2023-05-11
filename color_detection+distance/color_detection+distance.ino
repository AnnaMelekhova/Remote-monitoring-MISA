#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
  }
}

void loop() {
  // check if a color reading is available
  while (!APDS.colorAvailable()&&!APDS.proximityAvailable()) {
    delay(5);
  }
  String color="";
  int r, g, b;
  int proximity = APDS.readProximity();
  int distance = "";

if (proximity <= 50) {
  distance = 0;
} else if (proximity <= 175) {
  distance = 1;
} else if (proximity <= 215) {
  distance = 2;
} else if (proximity <= 235) {
  distance = 3;
} else if (proximity <= 240) {
  distance = 4;
} else if (proximity <= 242) {
  distance = 5;
} else if (proximity <= 244) {
  distance = 6;
} else if (proximity <= 248) {
  distance = 7;
} else if (proximity <= 249) {
  distance = 8;
} else if (proximity <= 250) {
  distance = 9;
} else {
  distance = 10;
}

// print the distance in centimeters
//Serial.print("Distance: ");
Serial.print(distance);
//Serial.println(" cm");
  APDS.readColor(r, g, b);


  if(r>g && r>b){
    color = "Red";
  }
  else if(g>r && g>b){
    color = "Green";
  }
  else if(b>r && b>r){
    color = "Blue";
  }
  else{
    color="Undefined";
  }
  //Serial.print("Color: ");
  Serial.print(",");
  Serial.println(color);

  delay(1000);
}
