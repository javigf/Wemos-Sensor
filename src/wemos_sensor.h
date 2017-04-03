#define DEBUG         				//COMMENT TO MOVE TO PRODUCTION

bool first_boot = 1;

#include "pins.h"
#include "security.h"
#include "filesys.h"
#include "product_data.h"
#include <ESP8266WiFi.h>          	//https://github.com/esp8266/Arduino
#include "ntp.h"
#include "users.h"
#include "serial_devices.h"
#include "oled_LCD.h"
#include "WiFi_Manager.h"
#include "telegram.h"
#include "bmp280.h"

//#include <ArduinoOTA.h> TODO :Check if needed



void handleNewMessages(int);
bool check_reboot(void);
