#include <SPI.h>
#include <WiFi101.h>

//Wifi Connection 
char ssid[] = "NathanE" ;
char pass[] = "Arduino1" ; 
int status = WL_IDLE_STATUS;
IPAddress server(192,168,0,101) ;
WiFiClient client;

//Sensor and Time Data
unsigned long timestamp [500] ;  
float voltage [500];
int interval = 5 ; 
int previousTime = 0 ; 
string message = string("string");  
float sensorToVoltage = (1.0/(7.5/(7.5+30.0))*(3.3/4095.0) ; 

void setup() 
{
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
    Serial.println("connected to server and ready to sense");
    // Make a HTTP request:

  }

}
//------------------------------------------------------------------------------


/* Infinite Loop */
void loop()
{
  //Read the sensors locally
  read_sensors() ; 
  
  //Create packets and send to server db
  Sending_To_phpmyadmindatabase();
  
  //Time delay of 30 seconds
  delay(30000); // interval
}
                         
void read_sensors()
{
   for (int i = 0 ; i < 500;)
   {
     if( timestamp - previousTime >= interval)
     {
       timestamp(i) = millis() ;
       voltage(i) = analogRead(A0) ;
       i = i + 1 ; 
     }
   }
}
                         


void Sending_To_phpmyadmindatabase()   //CONNECTING WITH MYSQL
{
  if (client.connect(server, 80)) 
  {
    for(int i  = 0 ; i < 500 ; i++)
     {
     voltage(i) = voltage(i)*sensorToVoltage ; 
     message = "GET /testcode/dht.php?temperature=" + String(voltage(i),4)) + ("&humidity=") + String(timestamp(i))
                  + " HTTP/1.1\r\n" + ("Host: 192.168.0.101\r\n") + ("Connection: close\r\n\r\n") ;
     client.print(message) ; 
     }
   
     //Serial.println("connected");
     // Make a HTTP request:
     //Serial.print("GET /testcode/dht.php?temperature=");
     //client.print("GET /testcode/dht.php?temperature=");     //YOUR URL
     //Serial.print(temperatureData);
     //client.print(temperatureData);
     //client.print("&humidity=");
     //Serial.print("&humidity=");
     //client.print(humidityData);
     //Serial.println(humidityData);
     //client.print(" ");      //SPACE BEFORE HTTP/1.1
     //client.print("HTTP/1.1");
     //client.println();
     //client.println("Host: 192.168.0.101");
     //client.println("Connection: close");
     //client.println(); 
    }

    
  else
  {
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
  
