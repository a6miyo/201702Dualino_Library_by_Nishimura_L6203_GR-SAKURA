
#include "arduino.h"
#include "Position_control.h"

#include "utility/first_communication.h"



//�R���X�g���N�^
Position_control::Position_control(short port,short motor)
{
	if(port>=0 && port<= 3)port_num = port;
	if(motor ==1 || motor == 2)Motor_num = motor;

}



void Position_control::setup(float gain)
{
	
		char motor_num;
		char port;
			
		port = port_num;//�����o�ϐ�������
		motor_num = Motor_num;//�����o�ϐ�������
		

//�ϐ�
	unsigned char Mode;
	int receive_data = 0; 
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	int gain_int = 0;
	unsigned char data[3]={0};

//�ݒ���e���M
	gain_int = gain *10000;
	
	if(motor_num == 1){
		Mode = 8;//���[�^1����ݒ胂�[�h
	}
	
	if(motor_num == 2){
		Mode = 9;//���[�^2����ݒ胂�[�h
	}
	
		first_com(port);	
	
		Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
		Dlno_Serial_write(Mode,port);//���[�h
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write( (unsigned char)(gain_int >> 8) ,port);	// ���[�^�[1���x����Q�C�� ���
		Dlno_Serial_write( (unsigned char)(gain_int &0xFF) ,port);	// ���[�^�[1���x����Q�C�� ����
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~
		Dlno_Serial_write(250,port);//�G���h�o�C�g
	
//�ݒ芮�����}��M
 Dlno_dataReceive(3,data,port);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*�f�o�b�N�p*/
/*
long Position_control1(int encr_resolution ,long angle,long *x_err,long *duty,long*x_ref,char port)
{
//�ϐ�
	unsigned char Mode = 10;//���[�^1���x����ݒ胂�[�h
	unsigned long reference_x1 =0x7FFFFF ;
	        
long encoder_x1_data;
        unsigned int Rx_data_new = 0;
	
        unsigned char Rx_data[17];
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;

//�ڕW�l�v�Z
reference_x1 =0x7FFFFF + ((angle * encr_resolution * 4 ) / 360);

	
	//Serial.println(reference_x1-0x7FFFFF);
//�ڕW�l���e���M
	Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
	Dlno_Serial_write(Mode,port);//���[�h
	Dlno_Serial_write( (unsigned char)(reference_x1>>16),port );
	Dlno_Serial_write( (unsigned char)(reference_x1 >>8) ,port);
	Dlno_Serial_write( (unsigned char)(reference_x1  &0xFF) ,port);	
	Dlno_Serial_write(1,port);
	Dlno_Serial_write(1,port);	// �_�~�[
	Dlno_Serial_write(1,port); //�_�~�[
	Dlno_Serial_write(1,port); //�_�~�[
	Dlno_Serial_write(250,port);//�G���h�o�C�g

//�G���R�[�_�f�[�^�擾
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
//�ϐ�
	
		char motor_num;
		char port;
			
		port = port_num;//�����o�ϐ�������
		motor_num = Motor_num;//�����o�ϐ�������
		
	
	unsigned char Mode;
	unsigned long reference_x =0x7FFFFF ;
	
	long encoder_data;

	
    long encoder_x1_data;
    unsigned int Rx_data_new = 0;
	
    unsigned char Rx_data[5];
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	
	if(motor_num == 1) Mode = 10;//���[�^1���x����ݒ胂�[�h
	if(motor_num == 2) Mode = 11;//���[�^1���x����ݒ胂�[�h
	

	
	//�ڕW�l�v�Z
	reference_x =0x7FFFFF + ((angle * encr_resolution * 4 ) / 360);
	//Serial.println(reference_x);
//�ڕW�l���e���M

	if(motor_num == 1){
		
		Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
		Dlno_Serial_write(Mode,port);//���[�h
		Dlno_Serial_write( (unsigned char)(reference_x>>16),port );
		Dlno_Serial_write( (unsigned char)(reference_x >>8) ,port);
		Dlno_Serial_write( (unsigned char)(reference_x  & 0xFF) ,port);	
		Dlno_Serial_write((unsigned char)(encr_resolution >> 8),port);
		Dlno_Serial_write((unsigned char)(encr_resolution  & 0xFF),port);	// �_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(250,port);//�G���h�o�C�g
	}
	
	if(motor_num == 2)
	{
		
		Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
		Dlno_Serial_write(Mode,port);//���[�h
		Dlno_Serial_write((unsigned char)(encr_resolution >> 8),port);
		Dlno_Serial_write((unsigned char)(encr_resolution  & 0xFF),port);
		Dlno_Serial_write( (unsigned char)(reference_x >>16),port );	
		Dlno_Serial_write( (unsigned char)(reference_x >>8),port);
		Dlno_Serial_write( (unsigned char)(reference_x  & 0xFF),port);
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(250,port);//�G���h�o�C�g
	
		Serial.print(encr_resolution);
		Serial.print(",");
	Serial.println(reference_x);
	}
	
//�G���R�[�_�f�[�^�擾
	Dlno_dataReceive(6,Rx_data,port);

	encoder_data = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
    return	encoder_data;

}

