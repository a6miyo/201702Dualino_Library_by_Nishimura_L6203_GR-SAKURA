
#ifndef DLNO_SERIAL_H
#define DLNO_SERIAL_H
		
		char Dlno_Serial_begin(unsigned int speed,char num =1 );
		int Dlno_Serial_write(unsigned char data, char num =1);
		int Dlno_Serial_read(char num =1);
		int Dlno_Serial_available(char num =1);
#endif
