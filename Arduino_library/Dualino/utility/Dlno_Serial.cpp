//////////////////////////////////////////////////////////////
//Dlno_Serial.c
//�R�`��w�@�R�쌤����
//���L ��j
////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////
//ArduinoMega,Due�Ȃǂ̃V���A���|�[�g�𑽐�����Arduino���畡����
//dsPIC�}�C�R���Ɏw�߂𑗐M����ꍇ�Ɏg�p�D
//Srial�֌W�̊֐��������Ń|�[�g�ԍ���ύX�ł���悤�ɂ��Ă���
//�|�[�g�ԍ���0�`3����I��
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
//ArduinoLeonardo,Da vinci�Ȃǂ̃V���A���|�[�g��1���������Ȃ�Arduino����
//dsPIC�}�C�R���Ɏw�߂𑗐M����ꍇ�Ɏg�p�D
//
//�|�[�g�ԍ���1�Œ肩��I��
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
