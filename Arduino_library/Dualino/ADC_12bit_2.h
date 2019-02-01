
#ifndef ADC_12BIT_h
#define ADC_12BIT_h

#include "arduino.h"
#include "utility/Dlno_dataReceive.h"
#include "utility/Dlno_Serial.h"


class ADC_12bit{

	private:
		short port_num;
	public:
		//�R���X�g���N�^�錾
		ADC_12bit(short port = 1);
		//�f�X�g���N�^
		~ADC_12bit(){};	
	
		void setup(unsigned int scan_ANx_Pin);
		int Read(char ch);

	
};

#endif

