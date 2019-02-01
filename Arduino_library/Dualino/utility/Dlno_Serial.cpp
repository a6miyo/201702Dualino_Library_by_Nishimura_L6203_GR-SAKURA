//////////////////////////////////////////////////////////////
//Dlno_Serial.c
//山形大学　山野研究室
//八鍬 一史
////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////
//ArduinoMega,Dueなどのシリアルポートを多数もつArduinoから複数の
//dsPICマイコンに指令を送信する場合に使用．
//Srial関係の関数を引数でポート番号を変更できるようにしておく
//ポート番号は0～3から選択
//
///////////////////////////////////////////////////////////


#include "arduino.h"
#include "Dlno_Serial.h"


//-----------Serial.begin------------------------------------

char Dlno_Serial_begin(unsigned int speed,char num )
{
	switch(num){
		case 0:
			Serial.begin(speed);
		Serial.println("num0");
			break;
		
		case 1:
			Serial1.begin(speed);
		Serial.println("num1(Serial1)");
			break;
		
		case 2:
			Serial2.begin(speed);
		Serial.println("num3(Serial2)");
			break;
		
		case 3:
			Serial3.begin(speed);
		Serial.println("num5(Serial3)");
			break;
		case 4:
			Serial4.begin(speed);
		Serial.println("num2(Serial4)");
			break;
		case 5:
			Serial5.begin(speed);
		Serial.println("num4(Serial5)");
			break;
		case 6:
			Serial6.begin(speed);
		Serial.println("num6(Serial6)");
			break;
		case 7:
			Serial7.begin(speed);
		Serial.println("num7(Serial7)");
			break;
		
		default:
			break;
	}
return 0;
}


//------------Serial.write--------------------------------------
int Dlno_Serial_write(unsigned char data, char num )
{
	
	int byte;

	switch(num){
		case 0:
			byte = Serial.write(data);
			return byte;
			break;
		
		case 1:
		    byte = Serial1.write(data);
			return byte;
			break;
		
		case 2:
		    byte = Serial2.write(data);
			return byte;
			break;
		
		case 3:
			byte = Serial3.write(data);
			return byte;
			break;
		
		case 4:
			byte = Serial4.write(data);
			return byte;
			break;
		
		
		case 5:
			byte = Serial5.write(data);
			return byte;
			break;
		
		
		case 6:
			byte = Serial6.write(data);
			return byte;
			break;
		
		
		case 7:
			byte = Serial7.write(data);
			return byte;
			break;
		
		
		default:
			return 0;		
			break;
	}
}


//--------------Serial.Read---------------------------------------
int Dlno_Serial_read(char num )
{
	
	int data ;
	switch(num){
		case  0:
			data = Serial.read();
			return data;
			break;
		
		case  1:
			  data = Serial1.read();
			return data;
			break;
		
		case 2:
			  data = Serial2.read();
			return data;
			break;
		
		case 3:
			  data = Serial3.read();
			return data;
			break;
		
		case 4:
			  data = Serial4.read();
			return data;
			break;
		
		case 5:
			  data = Serial5.read();
			return data;
			break;
		
		case 6:
			  data = Serial6.read();
			return data;
			break;
		
		case 7:
			  data = Serial7.read();
			return data;
			break;
		
		default:
			return 0;		
			break;
	}

}



//--------------Serial.available---------------------------------------

 int Dlno_Serial_available(char num )
{
	int data;
	switch(num){
		case 0:
			  data = Serial.available();
			return data;
			break;
		
		case 1:
			  data = Serial1.available();
			return data;
			break;
		
		case 2:
			  data = Serial2.available();
			return data;
			break;
		
		case 3:
			  data = Serial3.available();
			return data;
			break;
		
		case 4:
			  data = Serial4.available();
			return data;
			break;
		
		case 5:
			  data = Serial5.available();
			return data;
			break;
		
		case 6:
			  data = Serial6.available();
			return data;
			break;
		
		case 7:
			  data = Serial7.available();
			return data;
			break;
		
		default:
			return 0;		
			break;
	}

}


/////////////////////////////////////////////////////////////
//ArduinoLeonardo,Da vinciなどのシリアルポートを1つしか持たないArduinoから
//dsPICマイコンに指令を送信する場合に使用．
//
//ポート番号は1固定から選択
//
///////////////////////////////////////////////////////////

//-----------Serial.begin------------------------------------
/*
char Dlno_Serial_begin(unsigned int speed,char num )
{
	switch(num){
		case 1:
			Serial1.begin(speed);
			break;
		
		
		default:
			break;
	}
return 0;
}


//------------Serial.write--------------------------------------
int Dlno_Serial_write(unsigned char data, char num )
{
	
	int byte;

	switch(num){
		
		case 1:
		    byte = Serial1.write(data);
			return byte;
			break;
		
		default:
			return 0;		
			break;
	}
}


//--------------Serial.Read---------------------------------------
int Dlno_Serial_read(char num )
{
	
	int data ;
	switch(num){
		
		case  1:
			  data = Serial1.read();
			return data;
			break;
		
		default:
			return 0;		
			break;
	}

}



//--------------Serial.available---------------------------------------

 int Dlno_Serial_available(char num )
{
	int data;
	switch(num){
		
		case 1:
			  data = Serial1.available();
			return data;
			break;
				
		default:
			return 0;		
			break;
	}

}
*/
