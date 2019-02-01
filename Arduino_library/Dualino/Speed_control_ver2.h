
#ifndef SPEED_CONTROL_VER2_h
#define SPEED_CONTROL_VER2_h

//プロトタイプ宣言
#include "arduino.h"
#include "utility/Dlno_dataReceive.h"
#include "utility/Dlno_Serial.h"


class Speed_control_ver2{

	private:
		short port_num;
		short MOTOR_NUM;
	
		long Rpm_now;
		long Encr;
		signed short int Duty_data;
		short int Rpm_ref;
		long keW;
		
	public:
		//コンストラクタ宣言
		Speed_control_ver2(short port = 1,short motor = 1);
		//デストラクタ
		~Speed_control_ver2(){};
		
		void setupI(unsigned short int encr_resolution , unsigned long moter_max_rpm ,double K_v);
		void setupII(double Kt,double J,double R,unsigned char Vo);

		float control(int reference_speed,unsigned char brake_mode=0);
		float control_debug(int reference_speed,unsigned char brake_mode,short int pwm);
		
		float rpm(void);
		long count(void);
		short int DUTY(void);
			
		short int rpm_ref(void);
		long KeW(void);


	
};



#endif

