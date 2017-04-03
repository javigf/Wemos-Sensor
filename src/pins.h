//https://www.wemos.cc/product/d1-mini-pro.html
#define MAX_DIGITAL_PINS 9

//TODO VERIFY WHAT IS NEEDED AND WHY !

struct pin {
	
	//digital pins
	
	bool D[MAX_DIGITAL_PINS];
	//D0 IO - GPIO16 
	//D1 IO - GPIO05 - SCL/I2C
	//D2 IO - GPIO04 - SDA/I2C
	//D3 IO - GPIO0  - 10k Pull-up
	//D4 IO - GPIO02 - 10k Pull-up - BUILTIN LED
	//D5 IO - GPIO14 - SCK/SPI
	//D6 IO - GPIO12 - MISO/SPI
	//D7 IO - GPIO13 - MOSI/SPI
	//D8 IO - GPIO15 - SS/SPI - 10k Pull-down
	//Analog pins
	
	int A0;		// I - MAX 3.3V
			
} wemospin;



int pin_status (void);

int pin_status (){
	
	int i = 0;
	
	for (; i < 9; i++)
		wemospin.D[i] = digitalRead (i);
	
	
	return 0;
}
	