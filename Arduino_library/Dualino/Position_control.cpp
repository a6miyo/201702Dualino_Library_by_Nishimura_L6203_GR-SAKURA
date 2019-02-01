
#include "arduino.h"
#include "Position_control.h"

#include "utility/first_communication.h"



//コンストラクタ
Position_control::Position_control(short port,short motor)
{
	if(port>=0 && port<= 3)port_num = port;
	if(motor ==1 || motor == 2)Motor_num = motor;

}



void Position_control::setup(float gain)
{
	
		char motor_num;
		char port;
			
		port = port_num;//メンバ変数から代入
		motor_num = Motor_num;//メンバ変数から代入
		

//変数
	unsigned char Mode;
	int receive_data = 0; 
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	int gain_int = 0;
	unsigned char data[3]={0};

//設定内容送信
	gain_int = gain *10000;
	
	if(motor_num == 1){
		Mode = 8;//モータ1制御設定モード
	}
	
	if(motor_num == 2){
		Mode = 9;//モータ2制御設定モード
	}
	
		first_com(port);	
	
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write( (unsigned char)(gain_int >> 8) ,port);	// モーター1速度制御ゲイン 上位
		Dlno_Serial_write( (unsigned char)(gain_int &0xFF) ,port);	// モーター1速度制御ゲイン 下位
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミ
		Dlno_Serial_write(250,port);//エンドバイト
	
//設定完了合図受信
 Dlno_dataReceive(3,data,port);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*デバック用*/
/*
long Position_control1(int encr_resolution ,long angle,long *x_err,long *duty,long*x_ref,char port)
{
//変数
	unsigned char Mode = 10;//モータ1速度制御設定モード
	unsigned long reference_x1 =0x7FFFFF ;
	        
long encoder_x1_data;
        unsigned int Rx_data_new = 0;
	
        unsigned char Rx_data[17];
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;

//目標値計算
reference_x1 =0x7FFFFF + ((angle * encr_resolution * 4 ) / 360);

	
	//Serial.println(reference_x1-0x7FFFFF);
//目標値内容送信
	Dlno_Serial_write(200,port);//スタートバイト
	Dlno_Serial_write(Mode,port);//モード
	Dlno_Serial_write( (unsigned char)(reference_x1>>16),port );
	Dlno_Serial_write( (unsigned char)(reference_x1 >>8) ,port);
	Dlno_Serial_write( (unsigned char)(reference_x1  &0xFF) ,port);	
	Dlno_Serial_write(1,port);
	Dlno_Serial_write(1,port);	// ダミー
	Dlno_Serial_write(1,port); //ダミー
	Dlno_Serial_write(1,port); //ダミー
	Dlno_Serial_write(250,port);//エンドバイト

//エンコーダデータ取得
	Dlno_dataReceive(18,Rx_data,port);

	encoder_x1_data = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
   
    *x_err = ((long)Rx_data[4] <<24) + ((long)Rx_data[5] <<16) + ((long)Rx_data[6] << 8) + ((long)Rx_data[7]);
   	
	*duty = ((long)Rx_data[8] <<24) + ((long)Rx_data[9] <<16) + ((long)Rx_data[10] << 8) + ((long)Rx_data[11]);
   	
	*x_ref = ((long)Rx_data[12] <<24) + ((long)Rx_data[13] <<16) + ((long)Rx_data[14] << 8) + ((long)Rx_data[7]);
   	
	
	return	encoder_x1_data;
//encoder_x1_data =-8388607;



}
*/

long Position_control::control(int encr_resolution ,long angle)
{
//変数
	
		char motor_num;
		char port;
			
		port = port_num;//メンバ変数から代入
		motor_num = Motor_num;//メンバ変数から代入
		
	
	unsigned char Mode;
	unsigned long reference_x =0x7FFFFF ;
	
	long encoder_data;

	
    long encoder_x1_data;
    unsigned int Rx_data_new = 0;
	
    unsigned char Rx_data[5];
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	
	if(motor_num == 1) Mode = 10;//モータ1速度制御設定モード
	if(motor_num == 2) Mode = 11;//モータ1速度制御設定モード
	

	
	//目標値計算
	reference_x =0x7FFFFF + ((angle * encr_resolution * 4 ) / 360);
	//Serial.println(reference_x);
//目標値内容送信

	if(motor_num == 1){
		
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write( (unsigned char)(reference_x>>16),port );
		Dlno_Serial_write( (unsigned char)(reference_x >>8) ,port);
		Dlno_Serial_write( (unsigned char)(reference_x  & 0xFF) ,port);	
		Dlno_Serial_write((unsigned char)(encr_resolution >> 8),port);
		Dlno_Serial_write((unsigned char)(encr_resolution  & 0xFF),port);	// ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
	
	if(motor_num == 2)
	{
		
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write((unsigned char)(encr_resolution >> 8),port);
		Dlno_Serial_write((unsigned char)(encr_resolution  & 0xFF),port);
		Dlno_Serial_write( (unsigned char)(reference_x >>16),port );	
		Dlno_Serial_write( (unsigned char)(reference_x >>8),port);
		Dlno_Serial_write( (unsigned char)(reference_x  & 0xFF),port);
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	
		Serial.print(encr_resolution);
		Serial.print(",");
	Serial.println(reference_x);
	}
	
//エンコーダデータ取得
	Dlno_dataReceive(6,Rx_data,port);

	encoder_data = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
    return	encoder_data;

}

