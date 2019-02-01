
#include "arduino.h"
#include "Speed_control_ver2.h"
#include "utility/first_communication.h"

//コンストラクタ
Speed_control_ver2::Speed_control_ver2(short port,short motor)
{
	
	if(port>=0 && port<= 3)port_num = port;
	if(motor ==1 || motor == 2)MOTOR_NUM = motor;
	
	 Rpm_now=0;
	 Encr=0;
	 Duty_data=0;
	 Rpm_ref=0;
	 keW=0;
	
}


//メンバ関数実装
void Speed_control_ver2::setupI(unsigned short int encr_resolution , unsigned long moter_max_rpm ,double K_v )
{
	
	char motor_num;
	char port;
	
	port = port_num;//メンバ変数から代入
	motor_num = MOTOR_NUM;//メンバ変数から代入
	
	
//変数
	unsigned char Mode;//モータ1速度制御設定モード
	int receive_data = 0;
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
    unsigned int gain_int;
	unsigned char data[3]={0};
	
	//設定内容送信
	gain_int =(unsigned int)( K_v *100);

	if(motor_num == 1)Mode = 13;
	if(motor_num == 2)Mode = 16;
	
	first_com(port);
	
	
	Dlno_Serial_write(200,port);//スタートバイ
    Dlno_Serial_write(Mode,port);//モード
  
	Dlno_Serial_write( (unsigned char)(moter_max_rpm>>8) ,port);	// モーター1最大連続トルク時回転数(rpm)上位
    Dlno_Serial_write( (unsigned char)(moter_max_rpm &0xFF) ,port);	// モーター1最大連続トルク時回転数(rpm)下位
    Dlno_Serial_write( (unsigned char)(encr_resolution >>8),port); 
	Dlno_Serial_write( (unsigned char)(encr_resolution &0xFF),port);
    Dlno_Serial_write( (unsigned char)(gain_int>>8),port );	// モーター1速度制御ゲイン 上位
    Dlno_Serial_write( (unsigned char)(gain_int &0xFF) ,port);	// モーター1速度制御ゲイン 下位
    Dlno_Serial_write(1,port);	//ダミー
  
	Dlno_Serial_write(250,port);//エンドバイト

//設定完了合図受信

Dlno_dataReceive(3,data,port);
}


void Speed_control_ver2::setupII(double Kt,double J,double R,unsigned char Vo)
{
		
	char motor_num;
	char port;
	
	port = port_num;//メンバ変数から代入
	motor_num = MOTOR_NUM;//メンバ変数から代入
	
	
	
//変数
	unsigned char Mode;//モータ1速度制御設定モード
	 
	int receive_data = 0;
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;     
	unsigned char data[3]={0};

	unsigned int int_Kt;
	unsigned int int_J;
	unsigned int int_R;
	//設定内容送信
 	
	if(motor_num == 1)Mode = 14;
	if(motor_num == 2)Mode = 17;
	
	
	int_Kt = Kt*100000;
	int_J = J * 100;
    int_R = R * 100;

	Dlno_Serial_write(200,port);//スタートバイ
    Dlno_Serial_write(Mode,port);//モード
       
	Dlno_Serial_write((unsigned char)(int_Kt>>8)	,port);	// モーター1最大連続トルク時回転数(rpm)上位
    Dlno_Serial_write((unsigned char)(int_Kt&0xFF) 	,port);	// モーター1最大連続トルク時回転数(rpm)下位
    Dlno_Serial_write((unsigned char)(int_J>>8)		,port );	// モーター1速度制御ゲイン 上位
    Dlno_Serial_write((unsigned char)(int_J&0xFF) 	,port);	// モーター1速度制御ゲイン 下位
    Dlno_Serial_write((unsigned char)(int_R >>8)	,port); 
	Dlno_Serial_write((unsigned char)(int_R&0xFF)	,port);
    Dlno_Serial_write((unsigned char)Vo,port);	// エンコーダ1分解能デー
    
	Dlno_Serial_write(250,port);//エンドバイト
	
//設定完了合図受信

Dlno_dataReceive(3,data,port);
}





float Speed_control_ver2::control(int reference_speed,unsigned char brake_mode)
{
	short motor_num;
	short port;
	
	port = port_num;//メンバ変数から代入
	motor_num = MOTOR_NUM;//メンバ変数から代入
	
//変数
	unsigned char Mode;//モータ1速度制御設定モード
	unsigned char data[16]={0};

	int pwm = 0;
	unsigned char mark_data = 0;
	
	if(reference_speed < 0)
	{
		mark_data = 0b00000001;
		reference_speed *= -1;
	}
//目標値内容送信
	if(motor_num == 1){
		Mode = 15;
	
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write(reference_speed ,port);
		Dlno_Serial_write(mark_data,port);
		Dlno_Serial_write(brake_mode ,port);
		Dlno_Serial_write((unsigned char)(pwm >>8),port);
		Dlno_Serial_write((unsigned char)(pwm &0xFF),port);
	    Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
	
	if(motor_num == 2){
		Mode = 18;
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write( reference_speed,port );
		Dlno_Serial_write( mark_data,port );
		Dlno_Serial_write(brake_mode,port);
	    Dlno_Serial_write(1,port);
		Dlno_Serial_write(1,port);
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
		//データ受信
	
	Dlno_dataReceive(16,data,port);
	
	//受信データ復元

	Rpm_now = ((long)data[0] <<24) + ((long)data[1] <<16) + ((long)data[2] << 8) + ((long)data[3]);
	//*Rpm_now = moter1_rpm;
	
	Encr = ((long)data[4] <<24) + ((long)data[5] <<16) + ((long)data[6] << 8) + ((long)data[7]);
	//*Encr = encoder1_data;
	
	Duty_data = ((short int)data[8] << 8) + ((short int)data[9]&0xFF);
	//*Duty = duty;
	
	Rpm_ref = ((short int)data[10] << 8) + ((short int)data[11]&0xFF);
	//*Rpm_ref = rpm_ref;
	
	keW = ((short int)data[12] << 8) + ((short int)data[13]&0xFF);
	
	
	//return encoder1_data;
	return (float)(Rpm_now/1000.0);
}




float Speed_control_ver2::control_debug(int reference_speed,unsigned char brake_mode,short int pwm)
{
	char motor_num;
	char port;
	
	port = port_num;//メンバ変数から代入
	motor_num = MOTOR_NUM;//メンバ変数から代入
	
	
//変数
	unsigned char Mode;//モータ1速度制御設定モード
	
	unsigned char Rx_data[15];
	
	unsigned char mark_data = 0;
	
        long encoder_data = 0;
        long moter_rpm = 0;
		int duty = 0;
	    int rpm_ref = 0;

	
	if(reference_speed < 0)
	{
		mark_data = 0b00000001;
		reference_speed *= -1;
	}
//目標値内容送信
	
	if(motor_num == 1){
		Mode = 15;
	
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write(reference_speed ,port);
		Dlno_Serial_write(mark_data,port);
		Dlno_Serial_write(brake_mode ,port);
		Dlno_Serial_write((unsigned char)(pwm >>8),port);
		Dlno_Serial_write((unsigned char)(pwm &0xFF),port);
	    Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
	
	if(motor_num == 2){
		Mode = 18;
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write( reference_speed,port );
		Dlno_Serial_write( mark_data,port );
		Dlno_Serial_write(brake_mode,port);
	    Dlno_Serial_write(1,port);
		Dlno_Serial_write(1,port);
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
		//データ受信
	
	Dlno_dataReceive(16,Rx_data,port);
	
	
//受信データ復元



	Rpm_now = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
	//*Rpm_now = moter1_rpm;
	
	Duty_data = ((short int)Rx_data[8] << 8) + ((short int)Rx_data[9]&0xFF);
	//*Duty = duty;
	
	
	Encr = ((long)Rx_data[4] <<24) + ((long)Rx_data[5] <<16) + ((long)Rx_data[6] << 8) + ((long)Rx_data[7]);
	//*Encr = encoder1_data;
	
	
	Rpm_ref = ((short int)Rx_data[10] << 8) + ((short int)Rx_data[11]&0xFF);
	//*Rpm_ref = rpm_ref;
	
	keW = ((short int)Rx_data[12] << 8) + ((short int)Rx_data[13]&0xFF);
	
	return (float)(moter_rpm/1000.0);
}

float Speed_control_ver2::rpm(void)
{
	float rpm=0.0;
	rpm = (float)Rpm_now/1000;
	return rpm;
}

long Speed_control_ver2::count(void)
{
return Encr;
}

short int Speed_control_ver2::DUTY(void)
{
return Duty_data;
}

short int Speed_control_ver2::rpm_ref(void)
{
return Rpm_ref;
}

long Speed_control_ver2::KeW(void)
{
return keW;
}

