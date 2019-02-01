
#include "arduino.h"
#include "Position_control_ver2.h"
#include "utility/first_communication.h"



//�R���X�g���N�^
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
			
			port = port_num;//�����o�ϐ�������
			motor_num = Motor_num;//�����o�ϐ�������
			
			ENCR_RESO = encrResolution;
	
	
			//�ϐ�
				unsigned char Mode;//���[�^1���x����ݒ胂�[�h
				
				int receive_data = 0;
				unsigned char Rx_data_new = 0;
				unsigned char count = 0;
				unsigned char Rx_comp_flag = 0;     
				
				
				unsigned int int_K_p = 0;
				unsigned int int_K_v = 0;
				unsigned char data[3]={0,0,0};

				
				int_K_p = K_p *100;
				int_K_v = K_v *100;
				
	
			//�ݒ���e���M
			if(motor_num == 1)Mode = 19;
			if(motor_num == 2)Mode = 22;	
				
				Serial.println("first_com start");	
	
				first_com(port);
				
				Serial.println("first_com end");
				
	
				Dlno_Serial_write(200,port);//�X�^�[�g�o�C
			    Dlno_Serial_write(Mode,port);//���[�h
			  
				Dlno_Serial_write((unsigned char)(encrResolution >> 8),port);	// ���[�^�[1�ő�A���g���N����]��(rpm)���
			    Dlno_Serial_write((unsigned char)(encrResolution & 0xFF),port);	// ���[�^�[1�ő�A���g���N����]��(rpm)����
			    Dlno_Serial_write((unsigned char)(int_K_p >> 8),port); 
				Dlno_Serial_write((unsigned char)(int_K_p & 0xFF),port);
				Dlno_Serial_write((unsigned char)(int_K_v >> 8),port );	// ���[�^�[1���x����Q�C�� ���
			    Dlno_Serial_write((unsigned char)(int_K_v & 0xFF) ,port);	// ���[�^�[1���x����Q�C�� ����
			    Dlno_Serial_write(8,port);	//�_�~�[
			  
				Dlno_Serial_write(250,port);//�G���h�o�C�g
	
			//�ݒ芮�����}��M
			 Dlno_dataReceive(3,data,port);
	
	
	}







void Position_control_ver2::setupII(float Kt,float J,float R,unsigned char Vo)
{		
				char motor_num;
				char port;
				
				port = port_num;//�����o�ϐ�������
				motor_num = Motor_num;//�����o�ϐ�������
				
	
			//�ϐ�
				unsigned char Mode  ;//���[�^1���x����ݒ胂�[�h
				
				int receive_data = 0; 
				unsigned char count = 0;
				unsigned char Rx_comp_flag = 0;
				unsigned char data[3]={0};
				
				unsigned int int_Kt;
				unsigned int int_J;
				unsigned int int_R;
			//�ݒ���e���M
			if(motor_num == 1)Mode=20;
			if(motor_num == 2)Mode=23;	
			
				int_Kt = Kt*100000;
				int_J = J * 100;
			    int_R = R * 100;
				
				Dlno_Serial_write(200,port);//�X�^�[�g�o�C
			    Dlno_Serial_write(Mode,port);//���[�h
			       
				Dlno_Serial_write((unsigned char)(int_Kt>>8)	,port);	// ���[�^�[1�ő�A���g���N����]��(rpm)���
			    Dlno_Serial_write((unsigned char)(int_Kt&0xFF) 	,port);	// ���[�^�[1�ő�A���g���N����]��(rpm)����
			    Dlno_Serial_write((unsigned char)(int_J>>8)		,port );	// ���[�^�[1���x����Q�C�� ���
			    Dlno_Serial_write((unsigned char)(int_J&0xFF) 	,port);	// ���[�^�[1���x����Q�C�� ����
			    Dlno_Serial_write((unsigned char)(int_R >>8)	,port); 
				Dlno_Serial_write((unsigned char)(int_R&0xFF)	,port);
			    Dlno_Serial_write((unsigned char)Vo,port);	// �G���R�[�_1����\�f�[
			    
				Dlno_Serial_write(250,port);//�G���h�o�C�g
			//�ݒ芮�����}��M
			 Dlno_dataReceive(3,data,port);

		}
		
		
		
		
		
		
		long Position_control_ver2::control(long angle)
		{
			//Serial.println("into P control");
			
				char motor_num;
				char port;
				
				port = port_num;//�����o�ϐ�������
				motor_num = Motor_num;//�����o�ϐ�������
			
			//�ϐ�
				unsigned char Mode ;//���[�^1���x����ݒ胂�[�h
				unsigned long reference_x =0x7FFFFF ;
				        
				long encoder_x_data;
			    unsigned int Rx_data_new = 0;
				
			    unsigned char Rx_data[5];
				unsigned char count = 0;
				unsigned char Rx_comp_flag = 0;

			//�ڕW�l�v�Z
			    reference_x =reference_x + ((angle * ENCR_RESO * 4 ) / 360);
				
			//�ڕW�l���e���M
				if(motor_num == 1)Mode=21;
				if(motor_num == 2)Mode=24;	
		
			//Serial.println("into 1");
			
				Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
				Dlno_Serial_write(Mode,port);//���[�h
				Dlno_Serial_write( (unsigned char)(reference_x>>16),port );
				Dlno_Serial_write( (unsigned char)(reference_x >>8) ,port);
				Dlno_Serial_write( (unsigned char)(reference_x  &0xFF) ,port);	
				Dlno_Serial_write(1,port);
				Dlno_Serial_write(1,port);	// �_�~�[
				Dlno_Serial_write(1,port); //�_�~�[
				Dlno_Serial_write(1,port); //�_�~�[
				Dlno_Serial_write(250,port);//�G���h�o�C�g
		
			//�G���R�[�_�f�[�^�擾
				Dlno_dataReceive(16,Rx_data,port);///�����Œ�~��161025�B�����͌���Dlno_dataReceive(�u6�v,Rx_data,port)����250���A���Ă���̂��u16�v�̂Ƃ�������H
				//Serial.println("into 2");
		

				encoder_x_data = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
			    return	encoder_x_data;
			//encoder_x1_data =-8388607;

		}

