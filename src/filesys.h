//https://github.com/esp8266/Arduino/blob/master/doc/filesystem.md#file-system-object-spiffs

#include "FS.h"

bool init_spiff (void);
bool stop_spiff (void);
bool format_spiff (bool);
//bool open_file  ()
bool create_user_file (void);

///////////////////////////////////////////////////////////////////////////////////
// Init SPIFFS - Runs from setup ();
///////////////////////////////////////////////////////////////////////////////////

bool init_spiff (void){
        bool status;
        if (SPIFFS.begin())
                status = 1;
        else
                status = 0;

        return status;
}

///////////////////////////////////////////////////////////////////////////////////
// Stop SPIFFS
///////////////////////////////////////////////////////////////////////////////////

bool stop_spiff (void){
        SPIFFS.end();
        return 0;
}

///////////////////////////////////////////////////////////////////////////////////
// Format SPIFFS (if needed)
///////////////////////////////////////////////////////////////////////////////////
bool format_spiff (bool ignore){
        bool status;

        FSInfo fs_info;
        if ((!(SPIFFS.info(fs_info))) && (!(ignore))) {
 //               Serial.println ("Format required");
 //              Serial.println ("Formatting...");
                if (SPIFFS.format())
                        status = 1;
                else
                        status = 0;
        }
        else
                Serial.println ("Format not required");

        return status;
}

///////////////////////////////////////////////////////////////////////////////////
// Create user file
///////////////////////////////////////////////////////////////////////////////////
bool create_user_file (void){
        bool status = 0;

        if (!(SPIFFS.exists("/user.json"))) {
                Serial.println("Archivo de usuarios no existe");
                File f = SPIFFS.open("/user.json", "a");
                Serial.println("Creando el archivo de usuarios");
                if (!f) {
                        Serial.println("file open failed");
                }
                else{
                        status = 1;
                        Serial.println("Archivo de usuarios creado");
                      }
        }
        else
                Serial.println("el archivo ya existe");

        return status;
}
