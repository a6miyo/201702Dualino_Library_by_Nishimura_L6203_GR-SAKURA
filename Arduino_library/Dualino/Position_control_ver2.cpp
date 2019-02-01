
#include "arduino.h"
#include "Position_control_ver2.h"
#include "utility/first_communication.h"



//コンストラクタ
Position_control_ver2::Position_control_ver2(short port,short motor)
{
	if(port>=0 && port<= 7)port_num = port;
	if(motor ==1 || motor == 2)Motor_num = motor;
	 ENCR_RESO=0;
	
}


void Position_control_ver2::setupI(unsigned int encrResolution,float K_p,float K_v)
{
	
			char motor_num;
			char port;
			
			port = port_num;//メンバ変数から代入
			motor_num = Motor_num;//メンバ変数から代入
			
			ENCR_RESO = encrResolution;
	
	
			//変数
				unsigned char Mode;//モータ1速度制御設定モード
				
				int receive_data = 0;
				unsigned char Rx_data_new = 0;
				unsigned char count = 0;
				unsigned char Rx_comp_flag = 0;     
				
				
				unsigned int int_K_p = 0;
				unsigned int int_K_v = 0;
				unsigned char data[3]={0,0,0};

				
				int_K_p = K_p *100;
				int_K_v = K_v *100;
				
	
			//設定内容送信
			if(motor_num == 1)Mode = 19;
			if(motor_num == 2)Mode = 22;	
				
				Serial.println("first_com start");	
	
				first_com(port);
				
				Serial.println("first_com end");
				
	
				Dlno_Serial_write(200,port);//スタートバイ
			    Dlno_Serial_write(Mode,port);//モード
			  
				Dlno_Serial_write((unsigned char)(encrResolution >> 8),port);	// モーター1最大連続トルク時回転数(rpm)上位
			    Dlno_Serial_write((unsigned char)(encrResolution & 0xFF),port);	// モーター1最大連続トルク時回転数(rpm)下位
			    Dlno_Serial_write((unsigned char)(int_K_p >> 8),port); 
				Dlno_Serial_write((unsigned char)(int_K_p & 0xFF),port);
				Dlno_Serial_write((unsigned char)(int_K_v >> 8),port );	// モーター1速度制御ゲイン 上位
			    Dlno_Serial_write((unsigned char)(int_K_v & 0xFF) ,port);	// モーター1速度制御ゲイン 下位
			    Dlno_Serial_write(8,port);	//ダミー
			  
				Dlno_Serial_write(250,port);//エンドバイト
	
			//設定完了合図受信
			 Dlno_dataReceive(3,data,port);
	
	
	}







void Position_control_ver2::setupII(float Kt,float J,float R,unsigned char Vo)
{		
				char motor_num;
				char port;
				
				port = port_num;//メンバ変数から代入
				motor_num = Motor_num;//メンバ変数から代入
				
	
			//変数
				unsigned char Mode  ;//モータ1速度制御設定モード
				
				int receive_data = 0; 
				unsigned char count = 0;
				unsigned char Rx_comp_flag = 0;
				unsigned char data[3]={0};
				
				unsigned int int_Kt;
				unsigned int int_J;
				unsigned int int_R;
			//設定内容送信
			if(motor_num == 1)Mode=20;
			if(motor_num == 2)Mode=23;	
			
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
		
		
		
		
		
		
		long Position_control_ver2::control(long angle)
		{
			//Serial.println("into P control");
			
				char motor_num;
				char port;
				
				port = port_num;//メンバ変数から代入
				motor_num = Motor_num;//メンバ変数から代入
			
			//変数
				unsigned char Mode ;//モータ1速度制御設定モード
				unsigned long reference_x =0x7FFFFF ;
				        
				long encoder_x_data;
			    unsigned int Rx_data_new = 0;
				
			    unsigned char Rx_data[5];
				unsigned char count = 0;
				unsigned char Rx_comp_flag = 0;

			//目標値計算
			    reference_x =reference_x + ((angle * ENCR_RESO * 4 ) / 360);
				
			//目標値内容送信
				if(motor_num == 1)Mode=21;
				if(motor_num == 2)Mode=24;	
		
			//Serial.println("into 1");
			
				Dlno_Serial_write(200,port);//スタートバイト
				Dlno_Serial_write(Mode,port);//モード
				Dlno_Serial_write( (unsigned char)(reference_x>>16),port );
				Dlno_Serial_write( (unsigned char)(reference_x >>8) ,port);
				Dlno_Serial_write( (unsigned char)(reference_x  &0xFF) ,port);	
				Dlno_Serial_write(1,port);
				Dlno_Serial_write(1,port);	// ダミー
				Dlno_Serial_write(1,port); //ダミー
				Dlno_Serial_write(1,port); //ダミー
				Dlno_Serial_write(250,port);//エンドバイト
		
			//エンコーダデータ取得
				Dlno_dataReceive(16,Rx_data,port);///ここで停止中161025。原因は元はDlno_dataReceive(「6」,Rx_data,port)だが250が帰ってくるのが「16」のときだから？
				//Serial.println("into 2");
		

				encoder_x_data = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
			    return	encoder_x_data;
			//encoder_x1_data =-8388607;

		}

