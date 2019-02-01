
#include "arduino.h"
#include "Speed_control.h"
#include "utility/first_communication.h"





//変数レシーブデータの定義をしわすれている。

//ゲインの計算方法、geinを別int型変数にする
//エンドバイトが200になってる
//レシーブデータが悪さしている、データをdata_RX_newにいれなきゃいけない


//グローバル変数



//コンストラクタ
Speed_control::Speed_control(short port,short motor)
{
	if(port>=0 && port<= 3)port_num = port;
	if(motor ==1 || motor == 2)Motor_num = motor;
	
}


void Speed_control::setup(unsigned short int encr_resolution , unsigned long moter_max_rpm ,float gain)
{
	char motor_num;
	char port;
	
	port = port_num;//メンバ変数から代入
	motor_num = Motor_num;//メンバ変数から代入
	
	
//変数
	unsigned char Mode;//モータ1速度制御設定モード
	int receive_data = 0;
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
    int gain_int;
	unsigned char data[3]={0};

	if(motor_num == 1)Mode = 3;
	if(motor_num == 2)Mode = 4;
	//設定内容送信
	first_com(port);

	gain_int =(int)( gain *1000000);


	
	Dlno_Serial_write(200,port);//スタートバイ
    Dlno_Serial_write(Mode,port);//モード
    Dlno_Serial_write(1,port);	// エンコーダ1分解能デー
    Dlno_Serial_write( (unsigned char)(moter_max_rpm>>8) ,port);	// モーター1最大連続トルク時回転数(rpm)上位
    Dlno_Serial_write( (unsigned char)(moter_max_rpm &0xFF) ,port);	// モーター1最大連続トルク時回転数(rpm)下位
    Dlno_Serial_write( (unsigned char)(gain_int>>8),port );	// モーター1速度制御ゲイン 上位
    Dlno_Serial_write( (unsigned char)(gain_int &0xFF) ,port);	// モーター1速度制御ゲイン 下位
    Dlno_Serial_write((unsigned char)(encr_resolution >>8),port); //ダミー
	Dlno_Serial_write((unsigned char)(encr_resolution &0xFF),port); //ダミー
    Dlno_Serial_write(250,port);//エンドバイト

//設定完了合図受信

Dlno_dataReceive(3,data,port);
}

//エンコーダ分解能データは1byteで足りるのか
//引数としてモーター最大回転数はどの回転数で与えるべきなのか


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long Speed_control::control(char reference_speed , unsigned char brake_mode)
{
	
	char motor_num;
	char port;
	
	port = port_num;//メンバ変数から代入
	motor_num = Motor_num;//メンバ変数から代入
	
	
//変数
	unsigned char Mode;//モータ1速度制御設定モード
	
	unsigned char Rx_data[9];
	
	unsigned char mark_data = 0;	
    long encoder_data = 0;
    long moter_rpm = 0;


	if(reference_speed < 0)
	{
		mark_data = 0b00000001;
		reference_speed *= -1;
	}

//目標値内容送信
	if(motor_num == 1){
		Mode = 5;
		
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write(reference_speed ,port);
		Dlno_Serial_write(1,port);
		Dlno_Serial_write(mark_data,port);
		Dlno_Serial_write(brake_mode ,port);
		Dlno_Serial_write(1,port);
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
	
	else if(motor_num == 2){
		Mode = 6;
		
		Dlno_Serial_write(200,port);//スタートバイト
		Dlno_Serial_write(Mode,port);//モード
		Dlno_Serial_write(1,port);
		Dlno_Serial_write( reference_speed,port );
		Dlno_Serial_write( mark_data,port );
		Dlno_Serial_write(1 ,port);
		Dlno_Serial_write(brake_mode,port);
	    Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(1,port); //ダミー
		Dlno_Serial_write(250,port);//エンドバイト
	}
		
		//データ受信
	
	Dlno_dataReceive(10,Rx_data,port);
//受信データ復元
moter_rpm = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
encoder_data = ((long)Rx_data[4] <<24) + ((long)Rx_data[5] <<16) + ((long)Rx_data[6] << 8) + ((long)Rx_data[7]);

return moter_rpm;
}

//・モーター毎に関数を分けた方がよいのか



