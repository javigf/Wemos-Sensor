
#define I2C_DEVICES					//REQUIRED IF I2C_DEVICES ARE CONNECTED
#define SAVE_I2C_ADDRESSES			// COMMENT OUT IF NEED TO SAVE I2C_ADDRESSES
#include <Wire.h>

#define SCL_PIN    			5 		// GPIO5
#define SDA_PIN    			4 		// GPIO4

#ifdef SAVE_I2C_ADDRESSES
#define MAX_I2C_DEVICES  	127  	// MAX i2c Addresses
byte i2c_addresses [MAX_I2C_DEVICES];
#endif

int init_i2c (void);
int scan_i2c_devices (void);

int init_i2c (void){
								Wire.begin(SCL_PIN, SDA_PIN);

								return 0;
}

int scan_i2c_devices (void){
								byte error, address = 1;
								int nDevices = 0;

								for(; address < MAX_I2C_DEVICES; address++ ) {
																// The i2c_scanner uses the return value of
																// the Write.endTransmisstion to see if
																// a device did acknowledge to the address.
																Wire.beginTransmission(address);
																error = Wire.endTransmission();

																if (error == 0) {
																								Serial.print("I2C device found at address 0x");
																								if (address<16)
																																Serial.print("0");
																								Serial.print(address,HEX);
																								Serial.println("");

																								nDevices++;
#ifdef SAVE_I2C_ADDRESSES
																								i2c_addresses [address] = address;
#endif
																}
																else if (error == 4) {
																								Serial.print("Unknow error at address 0x");
																								//if (address<16)
																								//								Serial.print("0");
																								//Serial.println(address,HEX);
																}
								}
/*
								if (nDevices == 0)
																Serial.println("No I2C devices found\n");
								else
																Serial.println("done\n");

*/
								return nDevices;
}
