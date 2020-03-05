#include <SPI.h>
#include <WiFi101.h>

char ssid[] = "NathanE" ;
char pass[] = "Arduino1" ; 

int status = WL_IDLE_STATUS;
unsigned long humidityData = 0 ; 

IPAddress server(192,168,0,101) ;
WiFiClient client;
 
float temperatureData;




void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  Serial.println("Connected to wifi");
  printWiFiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:

  }

}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop(){
   for (int i = 0 ; i <=500;i++)
    {
      Sending_To_phpmyadmindatabase(); 
    }
  delay(120000); // interval
}


  void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
 {
   if (client.connect(server, 80)) 
   {
     temperatureData = analogRead(A0)*(3.3/4095.0)*(1.0/(7.5/(7.5+30.0)));
     humidityData = millis()  ; 
     //Serial.println("connected");
     // Make a HTTP request:
     //Serial.print("GET /testcode/dht.php?temperature=");
     client.print("GET /testcode/dht.php?temperature=");     //YOUR URL
     //Serial.print(temperatureData);
     client.print(temperatureData);
     client.print("&humidity=");
     //Serial.print("&humidity=");
     client.print(humidityData);
     //Serial.println(humidityData);
     client.print(" ");      //SPACE BEFORE HTTP/1.1
     client.print("HTTP/1.1");
     client.println();
     client.println("Host: 192.168.0.101");
     client.println("Connection: close");
     client.println(); 
    }

    
    else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
 }

 
void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
  
