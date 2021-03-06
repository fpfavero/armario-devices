#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>

#ifndef Configs_h
#define Configs_h

// Temp Vars
extern int lockerRelayPin = 6;
extern int lockerButtonPin = 5;

extern String LOCKER_NAME = "16";
// Topics to Subscribe
#define OPEN_DISPLAY_TOPIC "xxxxxxx/<#diplay>/open_display"
// Topics to Publish
#define  DISPLAY_CLOSED_TOPIC "xxxxxxx/<#diplay>/display_closed"
#define  DEVICE_PICKED_TOPIC "xxxxxxx/<#diplay>/device_picked"
#define  DEVICE_RETURNED_TOPIC  "xxxxxxx/<#diplay>/device_returned"

// Modes
#define PICKING_MODE "PICKING_MODE"
#define IDLE_MODE "IDLE_MODE"

// Hardware
#define numberOfDevices 15
extern const int  PWMMaxValue = 15;
extern const int  PWMEffectInterval = 100; // Time that each led wait to start fading to create a cool effect
extern const int  SensorReadingThreshold = 500; // Value that divide occupied dock or not
extern const int ledsPins[15] = { 22, 24, 26, 28, 30, 32, 34, 36, 23, 25, 27, 29, 31, 33, 35 }; //37
extern const int sensorPins[15] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14 };
extern boolean dockIsOcupied[15] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };
extern boolean waitingDoorToOpen = false;

// WiFi configs
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno
#define IP_ADDR_LEN     4   // Length of IP address in bytes

extern char ap_ssid[] = “<ssid>“;                  // SSID of network
extern char ap_password[] = “<pwd>“;          // Password of network
extern unsigned int ap_security = WLAN_SEC_WPA2; // Security of network
extern unsigned int timeout = 30000;             // Milliseconds

// Pub Sub
extern IPAddress pubSubServer(104, 154, 40, 75);
  
#endif
