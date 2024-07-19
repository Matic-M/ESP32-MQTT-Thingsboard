#include <ETH.h>
#include <TE_SM9000.h>
#include <SparkFun_PHT_MS8607_Arduino_Library.h>
#include <PubSubClient.h>
#include <Wire.h>

//EthernetClient ethClient; // not working with PubSubClient, error -2
WiFiClient ethClient;
PubSubClient client(ethClient);
MS8607 ms8607; // temperature, humidity, pressure
SM9000_sensor sm9333(125, -125, -26215, 26214); // differential pressure

const char* mqtt_server = "broker.hivemq.com"; // mqtt server
const uint16_t port = 1883; // unencrypted mqtt port
const char* mqtt_topic = "ONTKS/Projekt_Matic_Mubi"; // topic
String id = "esp32cl"; // mqtt id

void setup() {
  Serial.begin(115200);
  // Start Ethernet and wait for a DHCP-assigned IP
  if (!ETH.begin()) {
    Serial.println("Failed to configure Ethernet using DHCP");
    while (true) {
      delay(1000);
    }
  }

  Serial.println("Ethernet configured via DHCP");
    // Get and print local IP address
  Serial.print("IP Address: ");
  Serial.println(ETH.localIP());

  // Get and print subnet mask
  Serial.print("Subnet Mask: ");
  Serial.println(ETH.subnetMask());

  // Get and print gateway IP address
  Serial.print("Gateway: ");
  Serial.println(ETH.gatewayIP());

  // Get and print DNS server IP address
  Serial.print("DNS Server: ");
  Serial.println(ETH.dnsIP());

/*
  // Initialize Ethernet connection
  Ethernet.begin(mac);
  while (Ethernet.linkStatus() == 0) {
    delay(500);
    Serial.println("Connecting to Ethernet...");
  }
  Serial.println("Ethernet connected!");
*/  

  // Initialize MQTT connection
  client.setServer(mqtt_server, port);

  // Initialize sensors
  Wire.begin();
  ms8607.begin();
  //sm9333.begin();
}

void loop() {
  // Connect to MQTT
  if (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    Serial.print("Attempting MQTT connection to ");
    Serial.print(mqtt_server);
    Serial.print("...");
    delay(2000);
    if (!client.connect(id.c_str())) {
      Serial.print("MQTT connection failed! Error code = ");
      Serial.println(client.state());
      delay(5000);
      return;  // Exit the void function
    }
  }
  
  sm9333.wake();
  delay(2000);
  sm9333.readData();

  // Read sensor data
  float temperature = ms8607.getTemperature();
  float humidity = ms8607.getHumidity();
  float pressure = ms8607.getPressure();
  float differentialPressure = sm9333.getPressure();

  // Publish sensor data to MQTT
  char message[100];
  snprintf(message, sizeof(message), "[{\"temperature\": %.2f}, {\"humidity\": %.2f}, {\"pressure\": %.2f}, {\"diff_pressure\": %.2f}]", temperature, humidity, pressure, differentialPressure);
  client.publish(mqtt_topic, message);
  
  
  delay(5000);
}
