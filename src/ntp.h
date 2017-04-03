#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Time.h> //http://playground.arduino.cc/Code/Time
#include <TimeLib.h>
// TODO : Use friendly time library

String actual_time;
unsigned int actual_date;
bool time_status = 0; // 0 NOT UPDATED - 1 UPDATED
String local_epoch = "";

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

// You can specify the time server pool and the offset (in seconds, can be
// changed later with setTimeOffset() ). Additionaly you can specify the
// update interval (in milliseconds, can be changed using setUpdateInterval() ).
NTPClient timeClient(udp, "ar.pool.ntp.org", -10800, 60000);


int update_clk (void);

///////////////////////////////////////////////////////////////////////////////////
// Update Clock form NTP Server
///////////////////////////////////////////////////////////////////////////////////
int update_clk (void){

        timeClient.update();
        actual_time = timeClient.getFormattedTime();
        //actual_date = timeClient.getDay();

        return 0;
}

void digitalClockDisplay() {
        // digital clock display of the time
        actual_time = timeClient.getFormattedTime();
        //Serial.println (actual_time);

}
