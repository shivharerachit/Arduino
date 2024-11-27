#include <WiFi.h>
#include <HTTPClient.h>

// Replace with your network credentials
const char* ssid = "Rachit's Galaxy M21";
const char* password = "aqly2905";

// Replace with your ThingSpeak API key
const char* apiKey = "57302NOQLR4TQH6M";

// Define the analog pins connected to the potentiometers
const int potPin1 = 34; // Change this to the pin number of the first potentiometer
const int potPin2 = 35; // Change this to the pin number of the second potentiometer

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read the analog values from the potentiometers
  int potValue1 = analogRead(potPin1);
  int potValue2 = analogRead(potPin2);
  
  // Print the potentiometer readings to Serial Monitor
  Serial.print("Potentiometer 1 Reading: ");
  Serial.println(potValue1);
  Serial.print("Potentiometer 2 Reading: ");
  Serial.println(potValue2);
  
  // Send the potentiometer readings to ThingSpeak
  sendToThingSpeak(potValue1, potValue2);
  
  // Wait for 20 seconds before sending the next reading
  delay(8000);
}

void sendToThingSpeak(int value1, int value2) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Unable to send data to ThingSpeak.");
    return;
  }
  
  // Construct the URL for ThingSpeak update API
  String url = "http://api.thingspeak.com/update?api_key=";
  url += apiKey;
  url += "&field1=";
  url += String(value1);
  url += "&field2=";
  url += String(value2);
  
  // Send HTTP GET request to ThingSpeak
  HTTPClient http;
  http.begin(url);
  int httpResponseCode = http.GET();
  
  // Check the response code
  if (httpResponseCode == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.print("Error sending data to ThingSpeak. HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  
  // Close the connection
  http.end();
}


// is code me maine dono fields potentiometer wali li thi