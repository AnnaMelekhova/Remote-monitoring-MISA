import mqtt.*;
import processing.serial.*;

JSONObject message;

MQTTClient client;
String val; 
Serial myPort; 
String clr = "";
int cm =0;

void setup() 
{
  
  String portName = Serial.list()[4]; 
  myPort = new Serial(this, portName, 9600); 
  
  client = new MQTTClient(this);
  client.connect("mqtt://@demo.thingsboard.io");
  message = new JSONObject();
  
  message.setString("Color", clr);
  message.setFloat("Distance", cm);
  

  saveJSONObject(message, "data/new.json");

  clr = message.getString("Color");
  cm = message.getInt("Distance");

  println("Distance: " + cm +  ", Color" + clr);
}


void draw() 
{
  val = myPort.readStringUntil('\n');
  
  if (val != null) { 
      val = val.trim();
      
      String[] parts = val.split(",");

      if (parts.length >= 2) {
         clr = parts[1]; // the first element is the color
         cm = Integer.parseInt(parts[0].trim()); // the second element is the value, parsed as an integer
        
        //println("Color: " + clr);
        //println("Distance: " + cm);
        message.setString("Color", clr);
        message.setFloat("Distance", cm);
        
        println(message.toString()); 
        client.publish("v1/devices/me/telemetry", message.toString());
        delay(500);
      }
    else{
    println(val); 
    delay(500);
    }
 }
  
  
  
}


void clientConnected() {
  println("client connected");
  client.subscribe("v1/devices/me/telemetry");
}


void messageReceived(String topic, byte[] payload) {
  println("new message: " + topic + " - " + new String(payload));
}


void connectionLost() {
  println("connection lost");
}
