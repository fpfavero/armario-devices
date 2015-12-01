#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>

#ifndef Configs_h
#define Configs_h

// Temp Vars
extern int fakeLockerLedPin = 6;
extern int fakeLockerButtonPin = 5;

extern String LOCKER_NAME = "16";
// Topics to Subscribe
#define OPEN_DISPLAY_TOPIC "thegarage.ciandt.com/think.devices/16/open_display"
// Topics to Publish
#define  DISPLAY_CLOSED_TOPIC "thegarage.ciandt.com/think.devices/16/display_closed"
#define  DEVICE_PICKED_TOPIC "thegarage.ciandt.com/think.devices/16/device_picked"
#define  DEVICE_RETURNED_TOPIC  "thegarage.ciandt.com/think.devices/16/device_returned"

// Modes
#define PICKING_MODE "PICKING_MODE"
#define IDLE_MODE "IDLE_MODE"

// Hardware
#define numberOfDevices 1
extern const int ledsPins[16] = { 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
extern const int sensorPins[16] = { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15  };
extern boolean dockIsOcupied[16] = { false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false };

// WiFi configs
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno
#define IP_ADDR_LEN     4   // Length of IP address in bytes

extern char ap_ssid[] = "IOT";                  // SSID of network
extern char ap_password[] = "INTERNETOFTHINGS";          // Password of network
extern unsigned int ap_security = WLAN_SEC_WPA2; // Security of network
extern unsigned int timeout = 30000;             // Milliseconds

// Pub Sub
extern IPAddress pubSubServer(104, 154, 40, 75);

#endif
