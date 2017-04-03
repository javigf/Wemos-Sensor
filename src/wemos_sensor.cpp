/* TODO
   Group operation over user operation / Group MODE Privacy MODE
   http://stackoverflow.com/questions/37338101/how-to-add-a-bot-to-a-telegram-group
   Device
   Name
   Version
   Data

   User
   Master Password
   Admin Password
   User Password / Validaton
   Roles
   Blacklist
   Witelist

   Database to store User data

   Time based Scheduling
   Recurrence

   Manipulating I/O GPIO via Telegram

   Support Menu
   Format

   Extra features for ESP8266WiFi https://github.com/esp8266/Arduino/blob/master/doc/libraries.md
   PINOUT Wemos D1 Mini https://www.wemos.cc/product/d1-mini.html

 */

#include "Arduino.h"
#include "wemos_sensor.h"

void setup () {

        Serial.begin (115200);
        //I2C Devices
#ifdef I2C_DEVICES
        init_i2c ();
        int i2c_device_count = scan_i2c_devices ();

        // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
        display.begin(SSD1306_SWITCHCAPVCC, 0x3C);          // initialize with the I2C addr 0x3C (for the 128x64)
        // init done
        display_text ("I2C inicializado...");
        // Show image buffer on the display hardware.
        // Since the buffer is intialized with an Adafruit splashscreen
        // internally, this will display the splashscreen.
        //display.display();
        delay(1000);
#endif
        //set led pin as output
        pinMode (BUILTIN_LED, OUTPUT);
        // start ticker with 0.5 because we start in AP mode and try to connect
        ticker.attach (0.6, tick);

        //WiFiManager
        //Local intialization. Once its business is done, there is no need to keep it around
        WiFiManager wifiManager;
        //reset settings - for testing
        //wifiManager.resetSettings();
        display_text ("Inicializando WiFi...",1,0,0);
        delay(1000);
        //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
        wifiManager.setAPCallback (configModeCallback);

        //fetches ssid and pass and tries to connect
        //if it does not connect it starts an access point with the specified name
        //here  "AutoConnectAP"
        //and goes into a blocking loop awaiting configuration
        if (!wifiManager.autoConnect ()) {
                Serial.println ("failed to connect and hit timeout");
                //reset and try again, or maybe put it to deep sleep
                ESP.reset ();
                delay (100);
        }

        display_text ("WiFi OK",2,0,0);
        delay(1000);

        //if you get here you have connected to the WiFi
        //Serial.println ("connected...yeey :)");
        ticker.detach ();
        //keep LED off
        digitalWrite(BUILTIN_LED, HIGH);

        //Update Time first time in the Initialize
        timeClient.begin ();
        delay (10);
        update_clk ();
        // INIT SUPPORT DATA
        init_data ();
        // Filesystem
        init_spiff ();
        format_spiff (1);
        create_user_file ();
        // USERS DB
        init_users_db ();
        bme.begin ();
        init_message ();

}

void loop () {
        if (millis() > Bot_lasttime + Bot_mtbs)  {
// CLOCK
                digitalClockDisplay ();
                display_text (actual_time,2,15,5);
                bmp280 ();

                //  Serial.println (find_first_free_user_space ());

                if (first_boot) {
                        //bot.sendMessage((users[0].chatId),msg, "");

                        first_boot = 0;
                }
                int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

                while(numNewMessages) {
                        Serial.println("got response");
                        handleNewMessages(numNewMessages);
                        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
                }
                Bot_lasttime = millis();

        }

        // Function is triggered from user_menu.h
        if (rebootRequired)
                ESP.restart();
}
