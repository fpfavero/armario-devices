#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>
#include <PubSubClient.h>
#include <Bounce2.h>
#include <SoftPWM.h>
#include "Configs.h"

String currentMode = IDLE_MODE;

// WiFi
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
SFE_CC3000_Client wifiClient = SFE_CC3000_Client(wifi);
ConnectionInfo connection_info;

// Pub Sub
PubSubClient pubSubClient(wifiClient);

// Debouncer
Bounce debouncer = Bounce();

void setup() {
  Serial.begin(115000);
  Serial.println("Starting the board");
  initializePins();
  connectToWiFi();
  pubSubClient.setServer(pubSubServer, 1883);
  pubSubClient.setCallback(callback);
}

// the loop function runs over and over again forever
void loop() {
  checkWifiStatus();
  checkPubSub();
  processDockStatus();
  debouncer.update();
}

// ----------------------- main functions --------------------

void processDockStatus() {
  if (currentMode != IDLE_MODE) {
          Serial.println();
    for (int i = 0; i < numberOfDevices; i++) {
      boolean lastReading = checkIfDockIsOcupied(sensorPins[i]);
      delay(10);
      if (lastReading != dockIsOcupied[i]) {
        dockIsOcupied[i] = lastReading;
        if (lastReading) {
          fadeOut(ledsPins[i]);
          deviceReturned(i);
          Serial.print("device: ");
          Serial.print(i);
          Serial.println(" returned");
        } else {
          fadeIn(ledsPins[i]);
          devicePicked(i);
          Serial.print("device: ");
          Serial.print(i);
          Serial.println(" picked");
        }
      }
    }
  }
  boolean buttonPressed = !digitalRead(lockerButtonPin);
  if(currentMode == PICKING_MODE ){
    if(waitingDoorToOpen == true){
      if(buttonPressed)
      waitingDoorToOpen = false;
    }else if(buttonPressed){
      doorClosed();
      currentMode = IDLE_MODE;   
    }
  }
}

//void startPicking(){
//  // open the Door
//  openTheDoor();
//   // Turn on all availables devices
//   for(int i = 0; i < numberOfDevices; i++){
//     if(checkIfDockIsOcupied(sensorPins[i])){
//       dockIsOcupied[i] = true;
//     }else{
//       dockIsOcupied[i] = false;
//     }
//     fadeOut(ledsPins[i]);
//   }
//}

void startPickingAndReturning(byte* message, unsigned int length) {
  openTheDoor();
//  TO-DO: Interpretar o "message" para transformar em um array de numeros de docks.
//         Da forma que esta soh funciona de zero a nove.

  //Acende os leds que o usuario possui devices em uso
  for (int i = 0; i < length; i++) {
    char currentChar = (char)message[i];
    if (currentChar != ',') {
      fadeIn(ledsPins[int(currentChar) - '0']);
    }
  }
}

void openTheDoor() {
  // Turn on the Relay -- LOW state
  digitalWrite(lockerRelayPin, LOW);
  for (int j = 0; j < numberOfDevices; j++) {
    if (checkIfDockIsOcupied(sensorPins[j])) {
      dockIsOcupied[j] = true;
    } else {
      dockIsOcupied[j] = false;
    }
    fadeOut(ledsPins[j]);
  }
  waitingDoorToOpen = true;
  Serial.println("Waiting user to open de door");
}

void doorClosed() {
  // Turn on the Relay -- HIGH state  
  digitalWrite(lockerRelayPin, HIGH);
  Serial.println("Door Closed");
  for (int i = 0; i < numberOfDevices; i++) {
    fadeIn(ledsPins[i]);
  }
  pubSubClient.publish(DISPLAY_CLOSED_TOPIC, "");
}

void devicePicked(int deviceNumber) {
  char buf[4];
  itoa (deviceNumber, buf, 10);
  pubSubClient.publish(DEVICE_PICKED_TOPIC, buf);
}

void deviceReturned(int deviceNumber) {
  char buf[4];
  itoa (deviceNumber, buf, 10);
  pubSubClient.publish(DEVICE_RETURNED_TOPIC, buf);
}

// ----------------------- main functions --------------------

// ----------------------- Pub Sub Stuff ----------------------

void checkPubSub() {
  if (!pubSubClient.connected()) {
    for (int i = 0; i < numberOfDevices; i++) {
      fadeOut(ledsPins[i]);
    }
    reconnect();
  }
  pubSubClient.loop();
}


void reconnect() {
  // Loop until we're reconnected
  while (!pubSubClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (pubSubClient.connect("arduinoClient")) {
      Serial.println("connected");
      for (int i = 0; i < numberOfDevices; i++) {
        fadeIn(ledsPins[i]);
      }
      subscribeTopics();
    } else {
      Serial.print("failed, rc=");
      Serial.print(pubSubClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  char* message;
  currentMode = PICKING_MODE;
  startPickingAndReturning(payload, length);
  Serial.println("Picking Mode");
}

void subscribeTopics() {
  pubSubClient.subscribe(OPEN_DISPLAY_TOPIC);
}

// ----------------------- Pub Sub Stuff ----------------------

// ----------------------- Utils ----------------------

boolean checkIfDockIsOcupied(int pin) {
  int value = analogRead(pin);  // make an initial reading to set up the ADC
  delay(5);                // let the ADC stabilize
  value = analogRead(pin);      // toss the first reading and take one we will keep
  delay(1);                // delay again to be friendly to future readings
  Serial.print(value);
    Serial.print(" - ");
  delay(15);
  return value > 800 ? true : false;
}

void initializePins() {
  SoftPWMBegin();
  for (int i = 0; i < numberOfDevices; i++) {
    SoftPWMSet(ledsPins[i], 0);
    SoftPWMSetFadeTime(ledsPins[i], 1000, 1000);
    pinMode(sensorPins[i], INPUT);
    delay(10);
    dockIsOcupied[i] = checkIfDockIsOcupied(sensorPins[i]);
  }
  pinMode(lockerRelayPin, OUTPUT);
  digitalWrite(lockerRelayPin, HIGH);
  pinMode(lockerButtonPin, INPUT_PULLUP);

}

void initializeLockerSensor() {
  debouncer.attach(lockerButtonPin);
  debouncer.interval(100);
}


void fadeIn(int port) {
    SoftPWMSetPercent(port, 255);
}

void fadeOut(int port) {
    SoftPWMSetPercent(port, 0);
}

// ----------------------- Utils ----------------------


// ----------------------- WiFi Status ----------------

void connectToWiFi() {
  // Initialize CC3000 (configure SPI communications)
  if ( wifi.init() ) {
    Serial.println("CC3000 initialization complete");
  } else {
    Serial.println("Something went wrong during CC3000 init!");
  }

  // Connect using DHCP
  Serial.print("Connecting to SSID: ");
  Serial.println(ap_ssid);
  if (!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.println("Error: Could not connect to AP");
  }

  // Gather connection details and print IP address
  if ( !wifi.getConnectionInfo(connection_info) ) {
    Serial.println("Error: Could not obtain connection details");
  } else {
    Serial.print("IP Address: ");
    for (int i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(connection_info.ip_address[i]);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.println();
  }
}

void checkWifiStatus() {
  if (!wifi.getConnectionStatus()) {
    connectToWiFi();
  }
}

// ----------------------- WiFi Status ----------------
