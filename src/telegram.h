#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include "menu_guest.h"
#include "menu_common.h"
#include "menu_user.h"
#include "menu_admin.h"
#include "menu_support.h"

#define BOTtoken "311193128:AAGYJQzCk2BwdOwVSNu1r8Wn7Q2u5Exe880"  // your Bot Token (Get from Botfather)
String BOTpassword = "311193128";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 600;   //mean time between scan messages
long Bot_lasttime;    //last time messages' scan has been done
bool Start = false;
int ledStatus = 0;

//Requierd for Reading VCC for ESP8266
ADC_MODE(ADC_VCC);


/*struct telegramMessage{
   String text;
   String chat_id;
   String from_id;
   String from_name;
   String date;
   int update_id;
   };*/

// HELPFULL Links
// https://www.arduino.cc/en/Tutorial/StringComparisonOperators

int debug_telegram (int, String);
int init_message (void);

void handleNewMessages(int numNewMessages) {
        int position;

        for (int i=0; i<numNewMessages; i++) {
                String chat_id = String(bot.messages[i].chat_id);
                String text = bot.messages[i].text;

                String from_name = bot.messages[i].from_name;
                String message = "Dispositivo: " + contact_info.device_name +
                                 ".\n";

                //message =+ String(contact_info.dev_name) + ".\n" ;

                position = search_user_by_chatId (chat_id);

                String lcd_text = "Comando recibido" + text;
                display_text (lcd_text);

                // GUEST USER WITH NO PASSWORD
                if (( position == -1 ) && ( text != BOTpassword)) {
                        if (from_name == "")
                                from_name = "Invitado/a"; //TODO log in blacklist

                        message += "Bienvenido/a " + from_name + ".\n";
                        message += "Lamentablemente este usuario no tiene permisos o privilegios para efectuar actividad en este dispositivo.\n";

                        if (from_name != "Invitado/a")
                                message += "Código o comando desconocido" + text + ".\nSi tenés un código de validación ingresalo.\n" + BOTpassword + " \n";
                        //TODO : DEMO UNIT 1234
                        //TODO VERIFY WRONG CODE

                }
                // "GUEST" USER WITH VALID PASSWORD
                else if (( position == -1 ) && ( text == BOTpassword)) {
                        if (!(add_user (chat_id, from_name))) {
                                message += "Bienvenido/a " + from_name + ".\n";
                                message += "Ya podés utilizar el sistema .\n";
                                //TODO ADD BUTTONS/OPTIONS CALL /start
                        }
                        else // User DB has no available space
                                message += "Error al crear usuario " + from_name + ".\n";

                        //display_text (message);
                }

                // SUPPORT USER
                else if (position == 0) {
                        if (text.equalsIgnoreCase("usercount")) {
                                message =+"Hay usuarios en la base de datos";
                        }
                        else if (text.equalsIgnoreCase("test")) {
                                message =+"test";
                                Serial.println ("TEST");
                        }
                        else{
                                message =+"Comando desconocido";
                                Serial.println ("Comando desconocido");
                        }
                        /*if (text == BOTpassword) {
                                String keyboardJson = "[[\"Alta Usuario\"]]";

                                bot.sendMessageWithReplyKeyboard(chat_id, "Elija una opción", "", keyboardJson, true);
                           }*/
                }
                // ADMIN USER + NORMAL USER
                else if (position >= 1) {
/*						if ((text == "status") && (users [position].userValidated)) {
                                digitalWrite(BUILTIN_LED, LOW);
                        }
 */
                        if (((String) users [position].userRole == "admin") && (users [position].userValidated)) {
                                if (text.equalsIgnoreCase("clave")) { // Return the PASSWORD
                                        message =+"" + BOTpassword + ".\n";
                                }
                                else if (text.equalsIgnoreCase("nombre")) { // Return the PASSWORD
                                        message =+" nombre command.\n";
                                }

                        }
                        else if (users [position].userValidated) {
                                if (text.equalsIgnoreCase("status")) { // USER MENU
                                        message =+"Status Requested \n";
                                }
                        }
                }

                bot.sendMessage(chat_id, message, "");

                // VALIDATE ACCESS CODE

#ifdef DEBUG
                debug_telegram (i, message);
#endif
                // TODO: CALL TO MENUS
                // User Menu
                // Admin Menu
                // Support Menu

        }
}


int debug_telegram (int i, String message){

        //Serial.println("handleNewMessages");
        //Serial.println(String(numNewMessages));
        digitalWrite (BUILTIN_LED,LOW);
        delay (20);
        digitalWrite (BUILTIN_LED,HIGH);

        Serial.print ("Text:");
        Serial.println (bot.messages[i].text);

        Serial.print ("Chat ID:");
        Serial.println (bot.messages[i].chat_id);

        Serial.print ("From Name:");
        Serial.println (bot.messages[i].from_name);

        Serial.print ("From ID:");
        Serial.println (bot.messages[i].from_id);

        Serial.print ("Date:");
        Serial.println (bot.messages[i].date);

        Serial.print ("Mesagge:");
        Serial.println (message);

        return 0;
}

int init_message (void){
        String localString = contact_info.device_name;
        localString += "\nRSSI: ";
        localString +=  String (WiFi.RSSI ());
        localString += " db\n";
        localString += "SSID: " + String (WiFi.SSID());
        localString += "\nIP: ";
        localString += (WiFi.localIP().toString().c_str());

        display_text (localString,1,0,0);

        bot.sendMessage((users[0].chatId),localString, "");
        return 0;
}
