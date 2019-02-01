
#ifndef SPEED_CONTROL_h
#define SPEED_CONTROL_h

//�v���g�^�C�v�錾
#include "arduino.h"
#include "utility/Dlno_dataReceive.h"
#include "utility/Dlno_Serial.h"




class Speed_control{

	
	private:
		short port_num;
		short Motor_num;
	
	public:
		//�R���X�g���N�^�錾
		Speed_control(short port = 1,short motor = 1);
		//�f�X�g���N�^
		~Speed_control(){};
		
		void setup(unsigned short int encr_resolution , unsigned long moter_max_rpm ,float gain);
		long control(char reference_speed , unsigned char brake_mode);

};
#endif

