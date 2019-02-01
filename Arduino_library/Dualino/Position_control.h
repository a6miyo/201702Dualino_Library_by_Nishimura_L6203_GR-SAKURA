
#ifndef POSITION_CONTROL_h
#define POSITION_CONTROL_h


#include "utility/Dlno_dataReceive.h"
#include "utility/Dlno_Serial.h"


class Position_control{
	private:
		short port_num;
		short Motor_num;
		
	public:
		//�R���X�g���N�^�錾
		Position_control(short port = 1,short motor = 1);
		//�f�X�g���N�^
		~Position_control(){};	
		void setup(float gain);
		long control(int encr_resolution ,long angle);



};

#endif

