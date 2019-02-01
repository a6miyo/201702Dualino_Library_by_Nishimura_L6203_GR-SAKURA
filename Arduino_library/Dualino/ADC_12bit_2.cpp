#include "ADC_12bit_2.h"
#include "utility/first_communication.h"


//コンストラクタ
ADC_12bit::ADC_12bit(short port)
{
	if(port>=0 && port<= 3)port_num = port;
	else {
		port_num = 0;
	}
}


//////////////////////////////12bitADC設定関数//////////////////////////////////////////////////////////////////////////
void ADC_12bit::setup(unsigned int scan_ANx_Pin)
{
	
		char portnum;
			
		portnum = port_num;//メンバ変数から代入
	
//変数
	unsigned char Mode = 1;//ADC設定モード
	unsigned char data[3]={0};
	
	
	
 int first_Rx_comp_flag = 0;
 int count = 0;
 int receive_data = 0;
//設定内容送信
	first_com(portnum);
	
	Dlno_Serial_write(200,portnum);//スタートバイト
	Dlno_Serial_write(Mode,portnum);//モード
	Dlno_Serial_write((unsigned char)(scan_ANx_Pin >> 8),portnum);//scan_ANx_Pin(上位)
	Dlno_Serial_write((unsigned char)(scan_ANx_Pin & 0xFF),portnum);//scan_ANx_Pin(下位)
	Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー
    Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー	
    Dlno_Serial_write(250,portnum);//エンドバイト


   Dlno_dataReceive(3,data,portnum);

}


//////////////////////////////12bitADC実行関数//////////////////////////////////////////////////////////////////////////

int ADC_12bit::Read(char ch )
{
	
	
	char portnum;
		
	portnum = port_num;//メンバ変数から代入
//変数
	unsigned char Mode = 2;//ADC結果送信モード
	
	unsigned  char Rx_data[18] = {0};
	int ADC_data[9]={0};

//データ受信合図送信
	Dlno_Serial_write(200,portnum);//スタートバイト
	Dlno_Serial_write(Mode,portnum);//モード
	Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー
    Dlno_Serial_write(1,portnum);//ダミー
	Dlno_Serial_write(1,portnum);//ダミー	
	Dlno_Serial_write(250,portnum);//エンドバイト

	//ADC結果受信
	
	
  		Dlno_dataReceive(20,Rx_data,portnum);

			
	//ADC結果をchar型からint型へと復元
		ADC_data[0] = (Rx_data[0] << 8) + (Rx_data[1]);
		ADC_data[1] = (Rx_data[2] << 8) + (Rx_data[3]);
		ADC_data[2] = (Rx_data[4] << 8) + (Rx_data[5]);
		ADC_data[3] = (Rx_data[6] << 8) + (Rx_data[7]);
		ADC_data[4] = (Rx_data[8] << 8) + (Rx_data[9]);
		ADC_data[5] = (Rx_data[10] << 8) + (Rx_data[11]);
		ADC_data[6] = (Rx_data[12] << 8) + (Rx_data[13]);
		ADC_data[7] = (Rx_data[14] << 8) + (Rx_data[15]);
		ADC_data[8] = (Rx_data[16] << 8) + (Rx_data[17]);

	switch(ch)
	{
		case 0 :
			return ADC_data[0];
			break;
		case 1 :
			return ADC_data[1];
			break;
		case 2 :
			return ADC_data[2];
			break;
		case 3 :
			return ADC_data[3];
			break;
		case 4 :
			return ADC_data[4];
			break;
		case 5 :
			return ADC_data[5];
			break;
		case 6 :
			return ADC_data[6];
			break;
		case 7 :
			return ADC_data[7];
			break;
		case 8 :
			return ADC_data[8];
			break;

		default:
		break;
	}
}




