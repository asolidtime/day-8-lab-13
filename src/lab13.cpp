/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/home/maxwell/CTD-IoT/d8/lab13/src/lab13.ino"
/*
 * Project lab13
 * Description:
 * Author:
 * Date:
 */
#include "MQTT.h"
#include "oled-wing-adafruit.h"
#include "blynk.h"
void callback(char* topic, byte* payload, unsigned int length);
void setup();
void loop();
#line 10 "/home/maxwell/CTD-IoT/d8/lab13/src/lab13.ino"
OledWingAdafruit display;




void callback(char* topic, byte* payload, unsigned int length) 
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s",p);
  Serial.println();

	// //To parse an int
	// int receivedInt = atoi(p);
	// //To parse a float
	// float receivedFloat = atof(p);

	//To go from int to c_str
	// int i;
	// itoa(i, p, length); //destination int, c_str buffer, length

	if (String(p).equals("1")) {
    digitalWrite(D7, HIGH);
  } else if (String(p).equals("0")) {
    digitalWrite(D7, LOW);
  } else if (String(p).equals("high")) {
    digitalWrite(D8, HIGH);
  } else if (String(p).equals("low")) {
    digitalWrite(D8, LOW);
  } else {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.println(String(p));
    Serial.println(String(p));
    display.display();
  }
}

MQTT client("lab.thewcl.com", 1883, callback);

BLYNK_WRITE(V0) {
  if (param.asInt() == 1) {
    client.publish("maximus-ryan collaborative communication channel/blueledstate", "high"); 
  } else {
    client.publish("maximus-ryan collaborative communication channel/blueledstate", "low"); 

  }

}
BLYNK_WRITE(V1)
{
    client.publish("maximus-ryan collaborative communication channel/message1", param.asString());
}
// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  pinMode(D7, OUTPUT);
  Blynk.begin("QnAwxbXEtUAXJ_pHkObTkMagiLke5zMZ", IPAddress(167, 172, 234, 162), 8080);
    display.setup();
display.clearDisplay();
display.display();
  Serial.begin(115200);
  pinMode(D8, OUTPUT);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  display.loop();
  Blynk.run();
  // The core of your code will likely live here.
  if (client.isConnected()) {
  client.loop();
} else {
  Serial.println("connecting");
  client.connect(System.deviceID());
  Serial.println("connected");
  client.subscribe("oranges/message");
  client.publish("bananas/test", "test");
  client.publish("maximus-ryan collaborative communication channel/blueledstate", "low");
  client.publish("maximus-ryan collaborative communication channel/yellowledstate", "low");
  client.subscribe("maximus-ryan collaborative communication channel/message");
}
bool needsDelay = false;
if (display.pressedA()) {
  client.publish("oranges/lastoledpress", "A");
  needsDelay = true;
} else if (display.pressedB()) {
  client.publish("oranges/lastoledpress", "B");
  needsDelay = true;
} else if (display.pressedC()) {
  client.publish("oranges/lastoledpress", "C");
  needsDelay = true;
}
if (needsDelay) {
  delay(200);
}

}