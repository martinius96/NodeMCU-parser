// Author: Martin Chlebovec alias: martinius96
// Support: https://www.paypal.me/Chlebovec
// Personal web: https://arduino.php5.sk
// Email contact: martinius96@gmail.com
// Facebook contact: 100001242570317
// Use under license!
#include <ESP8266WiFi.h> //libraries included at Arduino Core!!
#include <WiFiClientSecure.h> //libraries included at Arduino Core!!
const char* ssid = "mywifiname";
const char* password = "mywifipass";
const char* host = "myweb.com"; //without https and without www
const int httpsPort = 443; //HTTPS port
const char* fingerprint = "00 9f 87 1d b1 85 be e6 bd 73 c1 8d 04 63 58 99 f0 32 43 92"; //SHA1 fingerprint
const int led = 16; //D0 pin

void setup() {
  pinMode(led, OUTPUT); //set led as output
  Serial.begin(115200);
  Serial.println();
  Serial.println("connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}


void loop() {

WiFiClientSecure client;
  if (!client.connect(host, httpsPort)) {
    return;
  }
  if (client.verify(fingerprint, host)) {
  }
  else {
  }
  String url = "/myrepositoryonwebserver/variable.txt";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "User-Agent: NodeMCU\r\n" + "Connection: close\r\n\r\n");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
  String line = client.readStringUntil('\n');
  if (line == "Start") {
    digitalWrite(led, HIGH);

  
  } else if (line == "Stop")  {
     digitalWrite(led, LOW);
  }



}

