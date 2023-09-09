/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.
  //////////////////////
date: 20 August

  reference from chatgpt
  

  // ESP32 Touch Sensor Read Example

// Include the required library
#include <Arduino.h>

// Define the touch sensor pin
const int touchPin = T3; // Replace with the desired touch pin (T0, T1, T2, T3, T4, T5, T6, T7, or T8)

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
}

void loop() {
  // Read the touch sensor value
  int touchValue = touchRead(touchPin);

  // Print the touch sensor value to the serial monitor
  Serial.print("Touch Sensor Value (");
  Serial.print(touchPin);
  Serial.print("): ");
  Serial.println(touchValue);

  // Add a delay for stability (adjust as needed)
  delay(1000);
}
-----------------------------
OSCmessage chatgpt

import oscP5.*;
import netP5.*;

OscP5 oscP5;
NetAddress myRemoteLocation;

void setup() {
  size(400, 400);
  frameRate(25);
  
  oscP5 = new OscP5(this, 12345);  // Set the port to listen for OSC messages
  myRemoteLocation = new NetAddress("192.168.1.177", 8888);  // IP and port of the Arduino sending OSC messages
}

void draw() {
  // Empty draw function (not needed for OSC reception)
}

void oscEvent(OscMessage msg) {
  // Print the received OSC message
  print("Received OSC: ");
  msg.print();
  println();

  // Extract and use the OSC values
  if (msg.checkAddrPattern("/example")) {
    int intValue = msg.get(0).intValue();
    float floatValue = msg.get(1).floatValue();
    String stringValue = msg.get(2).stringValue();
    
    println("Int Value: " + intValue);
    println("Float Value: " + floatValue);
    println("String Value: " + stringValue);
  }
}

Technical help: wei lin
--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "G05";          // your network SSID (name)
char pass[] = "CreativeFacilities";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(172,16,0,193);        // remote IP of your computer
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)


//conductive thread
const int sensor1 = touchRead(T3); 
const int sensor2 = touchRead(T8); 

int sensor3V = 10;


void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif

}

void loop() {
    OSCMessage msg("/test");
    msg.add("hello, osc.");
    Udp.beginPacket(outIp, outPort);
    msg.send(Udp);
    Udp.endPacket();
    msg.empty();
    delay(500);

     Serial.print("T3 = ");
    Serial.print(touchRead(T3));
    Serial.print("   "); 

     Serial.print("T8 = ");
    Serial.print(touchRead(T8));
    Serial.print("   "); 
    
}
