/////////////////////////////////////////////////////////////////
//Dlno_dataReceive.c
//�R�`��w  �R�쌤����
//���L  ��j
//////////////////////////////////////////////////////////////////


#include "Dlno_dataReceive.h"

void Dlno_dataReceive(char bytesize,unsigned char data[],char num)
{	
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	
	while(Rx_comp_flag == 0)
	{ 	
	
	  if(Dlno_Serial_available(num) > 0)//��M�o�b�t�@�Ƀf�[�^�����邩�`�F�b�N
	  {
	        Rx_data_new = Dlno_Serial_read(num); //�f�[�^��M
	  	  // 	Serial.println(Rx_data_new);
		//Serial.println("2");

	  	
	        if(count == 0) //count�l��0,�������͂���ȉ��̏ꍇ
	        {
	        	if(Rx_data_new == 200){ count++;//�X�^�[�g�o�C�g(200)�������Ă����Ƃ�
		//Serial.println("3");
	        	}
	        	else{ count = 0;                 //�X�^�[�g�o�C�g(200)�ł͂Ȃ��Ƃ��J�E���g������
		//Serial.println("4");
	        	}
	        }
	        else if(count > 0)//count�l��0�ȏ�̏ꍇ
	        {   
		//Serial.print("5 = ");
		//Serial.println(Rx_data_new);
	            data[(count - 1)] = Rx_data_new; //�z�� Rx_data[]�� �f�[�^�ۑ�
	            
	            count++;
	          
	        	if( count >= bytesize) //coun�l���G���h�o�C�g�������Ă���ł��낤�o�C�g���ɒB������
	            {
		//Serial.println("6");
	                if(Rx_data_new == 250){
	                    Rx_comp_flag = 1;
	                //	return 1;
		//Serial.println("7");
	                }
	                else{
		//Serial.println("8");
	                    Rx_comp_flag = 0;
	                    count = 0;
	                //	return 0;
	                }
	               
	            }
	        }
	   }    
	} 

}	



/*
void Dlno_dataReceive(char bytesize,unsigned char data[],char num)
{	
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	
	while(1)
	{ 	
	
	  if(Dlno_Serial_available(num) > 0)//��M�o�b�t�@�Ƀf�[�^�����邩�`�F�b�N
	  {
	        Rx_data_new = Dlno_Serial_read(num); //�f�[�^��M
	  	    int a = Rx_data_new;
	  		Serial.println(a);
	  }

	}
	}	

  */ 