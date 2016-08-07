// Send a Hello world UDP packet every 5 second to a specific device

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Connection to AP
const char ssid[] = "receiver_AP";     // Network SSID (name)
const char pass[] = "passw1234";       // Network password

// IP address of the device that we want to send a packet
IPAddress RXDevice_ip(192,168,1,1);

// Port to use
const unsigned int Port = 8888;

// Packet for send data
char TxPacket[] = "Hi, im node number 1"; // A string to send

// An EthernetUDP instance to let us send packets over UDP
WiFiUDP Udp;

void setup()
{
    Serial.begin(115200);
    Serial.println();
    
    // Connecting to a WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    // Connection success
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // Open UDP port
    Serial.println("Starting UDP");
    Udp.begin(Port);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
}

void loop()
{
    // Send a message, to the IP address and port of the specific device
    Udp.beginPacket(RXDevice_ip, Udp.localPort());
    Udp.write(TxPacket);
    Udp.endPacket();

    Serial.println(" ");
    Serial.println("Packet sended");

    // Wait 5 seconds
    delay(5000); 
}
