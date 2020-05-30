#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
int led=5;
const char *ssid = "Yout WiFi SSID";
const char *password = "Your WiFi Password";
String fingerprint, HEDRON, id,token, from, message, WebHook;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  delay(1000);
  Serial.begin(115200);

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("\n\n");
  Serial.print("Try to connect to WiFi. Please wait! ");
  Serial.print("\n\n");
  // Halt the code until connected to WiFi.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }
 
  // If connection is successful, turn control led(if used) on and write WiFi SSID to serial monitor along with assigned IPAddress.
  Serial.print("\n\n");
  Serial.print("-------------------------------------");
  Serial.print("\n\n");
  Serial.print("Connection is successful!");
  Serial.print("\n\n");
  Serial.print("Connected WiFi SSID : ");
  Serial.print(ssid);
  Serial.print("\n\n");
  Serial.println("Connected IPAddress : ");
  Serial.println(WiFi.localIP());
  Serial.print("\n\n"); 
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);

  fingerprint = "Your Fingerprint";

  HEDRON = "Your Hedron";
  id= "Your Id";
  token = "Your Token";
  from = "14155238886"; //Twillio Number
  String number[] = {"Phone 1", "Phone 2"}; //Use countrycode

  message = "Worked+Bitch!";
  for (int i=0; i<2; i++) {
    for(int j=0; j<10; j++) {
      if(j<5) {
        WebHook = "https://www.theamplituhedron.com/dashboard/WhatsApp-Web-Hook/" + HEDRON + ".php?id=" + id + "&token=" + token + "&body=" + message + "&from=" + from + "&to=" + number[i];
        sendMessage(WebHook, fingerprint);
        delay(30000);
      }
    }
  }

  delay(30000);
}
void sendMessage(String WebHook, String fingerprint) {
  HTTPClient http;
  
  // Send a request. 
  http.begin(WebHook, fingerprint);
  
  int httpCode = http.GET();           
  String payload = http.getString();    
  Serial.println(httpCode);
//  if(httpCode == 200){ Serial.println("\n Message Sent Successfully..."); }else{ Serial.println("\n Not Working! Error Code: " + httpCode); }
 
  // End HTTP Get Request.
  http.end();
}
