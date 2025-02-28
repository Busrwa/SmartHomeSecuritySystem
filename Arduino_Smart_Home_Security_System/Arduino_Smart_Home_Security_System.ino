#include <WiFi.h>
#include <WebServer.h>
#include <WiFi.h>
#include <HTTPClient.h> 


const char* ssid = "Busra's Phone";  // Wi-Fi SSID
const char* password = "123456789";  
const char* flask_server_ip = "http://example/";  


// HC-SR04 Ultrasonic Sensor
const int trigPin = 5;  // Trig pin (GPIO14)
const int echoPin = 18;  // Echo pin (GPIO12)

// Define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm, distanceInch;
long inches, cm;

WebServer server(80);  // Web server

// HTML Page
const String html_page = "<html><body><h1>Ultrasonic Distance Meter</h1><p>Distance: <span id='distance'></span> cm</p><script>setInterval(function(){fetch('/readDistance').then(response => response.json()).then(data => {document.getElementById('distance').textContent = data.cm;});}, 1000);</script></body></html>";

void MainPage() {
  server.send(200, "index/html", html_page);  
}

void Distance() {
  cm = distanceCm;
  inches = distanceInch;
  String data = "{\"cm\": " + String(cm) + ", \"inches\": " + String(inches) + "}";
  server.send(200, "application/json", data);  
}

void printWiFiStatus() {
  Serial.print("Wi-Fi status: ");
  Serial.println(WiFi.status());

  switch (WiFi.status()) {
    case WL_IDLE_STATUS:
      Serial.println("Wi-Fi status: Idle...");
      break;
    case WL_NO_SSID_AVAIL:
      Serial.println("Wi-Fi status: SSID not found!");
      break;
    case WL_SCAN_COMPLETED:
      Serial.println("Wi-Fi status: Scan completed.");
      break;
    case WL_CONNECTED:
      Serial.println("Wi-Fi status: Connected!");
      break;
    case WL_CONNECT_FAILED:
      Serial.println("Wi-Fi status: Connection failed!");
      break;
    case WL_DISCONNECTED:
      Serial.println("Wi-Fi status: Disconnected.");
      break;
    default:
      Serial.println("Wi-Fi status: Unknown status.");
      break;
  }
}

void setup() {
  Serial.begin(115200);  // Start serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  // Start Wi-Fi Connection
  WiFi.mode(WIFI_STA);  // Initialize Wi-Fi in STA mode
  WiFi.begin(ssid, password);  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    printWiFiStatus();  // Print detailed Wi-Fi status
    Serial.println("Retrying Wi-Fi connection...");
  }

  Serial.println("Connected to Wi-Fi");
  Serial.print("Your Local IP address is: ");
  Serial.println(WiFi.localIP());  // Print ESP32's IP address

  // Start the web server
  server.on("/", MainPage);  // Define the main page
  server.on("/readDistance", Distance);  // Define the distance reading page
  server.begin();  // Start the web server
}

void loop() {
  server.handleClient();  // Listen to web server requests

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;

  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);

   // Send HTTP request
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String serverPath = "http://example/data?cm=" + String(distanceCm) + "&inches=" + String(distanceInch);

    http.begin(serverPath);
    int httpResponseCode = http.GET();  // Send HTTP GET request

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response Code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error in HTTP request: ");
      Serial.println(httpResponseCode);
    }
    http.end();  // Close HTTP connection
  }

  delay(1000);  // Wait for 1 second
}
