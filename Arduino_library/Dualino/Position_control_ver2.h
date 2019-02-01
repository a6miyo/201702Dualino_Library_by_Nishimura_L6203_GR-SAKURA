
#ifndef POSITION_CONTROL_VER2_h
#define POSITION_CONTROL_VER2_h


#include "utility/Dlno_dataReceive.h"
#include "utility/Dlno_Serial.h"

class Position_control_ver2{

	private:
	    int ENCR_RESO;	
	    short port_num;
		short Motor_num;
		
	
	public:
		//コンストラクタ宣言
		Position_control_ver2(short port = 1,short motor = 1);
		//デストラクタ
		~Position_control_ver2(){};
	
		void setupI(unsigned int encrResolution,float K_p,float K_v);
		void setupII(float Kt,float J,float R,unsigned char Vo);

		long control(long angle);

};
#endif

