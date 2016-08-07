// Show incoming UDP packets

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// create an AP
const char ssid[] = "receiver_AP";     //  your network SSID (name)
const char pass[] = "passw1234";       //  your network password

// AP parameters
IPAddress ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// Port to use
const unsigned int Port = 8888;

// Packet for receive data
char RxPacket[UDP_TX_PACKET_MAX_SIZE]; // buffer to hold incoming packet

// An WifiUDP instance to let us receive packets over UDP
WiFiUDP Udp;

void setup()
{
    Serial.begin(115200);
    Serial.println();
    
    // Creating a WiFi network AP
    Serial.print("Creating AP ");
    Serial.println(ssid);
    WiFi.softAPConfig(ip,gateway,subnet);
    WiFi.softAP(ssid, pass);

    // Creation success
    Serial.println("");
    Serial.println("WiFi AP created");
    Serial.println("IP address: ");
    Serial.println(WiFi.softAPIP());

    // Open UDP port
    Serial.println("Starting UDP");
    Udp.begin(Port);
    Serial.print("Local port: ");
    Serial.println(Udp.localPort());
    Serial.println("");
}

void loop()
{
    // If there's data available, read a packet
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        // Show packet size
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = Udp.remoteIP();

        // Show tx device address and port
        for (int i = 0; i < 4; i++)
        {
            Serial.print(remote[i], DEC);
            if (i < 3)
                Serial.print(".");
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());
        
        // Read and show the packet data
        Udp.read(RxPacket, UDP_TX_PACKET_MAX_SIZE);
        Serial.print("Content of packet:");
        Serial.println(RxPacket);
    }
    delay(10);
}
