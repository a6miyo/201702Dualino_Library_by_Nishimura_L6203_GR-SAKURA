
#include "arduino.h"
#include "Speed_control.h"
#include "utility/first_communication.h"





//�ϐ����V�[�u�f�[�^�̒�`�����킷��Ă���B

//�Q�C���̌v�Z���@�Agein���int�^�ϐ��ɂ���
//�G���h�o�C�g��200�ɂȂ��Ă�
//���V�[�u�f�[�^���������Ă���A�f�[�^��data_RX_new�ɂ���Ȃ��Ⴂ���Ȃ�


//�O���[�o���ϐ�



//�R���X�g���N�^
Speed_control::Speed_control(short port,short motor)
{
	if(port>=0 && port<= 3)port_num = port;
	if(motor ==1 || motor == 2)Motor_num = motor;
	
}


void Speed_control::setup(unsigned short int encr_resolution , unsigned long moter_max_rpm ,float gain)
{
	char motor_num;
	char port;
	
	port = port_num;//�����o�ϐ�������
	motor_num = Motor_num;//�����o�ϐ�������
	
	
//�ϐ�
	unsigned char Mode;//���[�^1���x����ݒ胂�[�h
	int receive_data = 0;
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
    int gain_int;
	unsigned char data[3]={0};

	if(motor_num == 1)Mode = 3;
	if(motor_num == 2)Mode = 4;
	//�ݒ���e���M
	first_com(port);

	gain_int =(int)( gain *1000000);


	
	Dlno_Serial_write(200,port);//�X�^�[�g�o�C
    Dlno_Serial_write(Mode,port);//���[�h
    Dlno_Serial_write(1,port);	// �G���R�[�_1����\�f�[
    Dlno_Serial_write( (unsigned char)(moter_max_rpm>>8) ,port);	// ���[�^�[1�ő�A���g���N����]��(rpm)���
    Dlno_Serial_write( (unsigned char)(moter_max_rpm &0xFF) ,port);	// ���[�^�[1�ő�A���g���N����]��(rpm)����
    Dlno_Serial_write( (unsigned char)(gain_int>>8),port );	// ���[�^�[1���x����Q�C�� ���
    Dlno_Serial_write( (unsigned char)(gain_int &0xFF) ,port);	// ���[�^�[1���x����Q�C�� ����
    Dlno_Serial_write((unsigned char)(encr_resolution >>8),port); //�_�~�[
	Dlno_Serial_write((unsigned char)(encr_resolution &0xFF),port); //�_�~�[
    Dlno_Serial_write(250,port);//�G���h�o�C�g

//�ݒ芮�����}��M

Dlno_dataReceive(3,data,port);
}

//�G���R�[�_����\�f�[�^��1byte�ő����̂�
//�����Ƃ��ă��[�^�[�ő��]���͂ǂ̉�]���ŗ^����ׂ��Ȃ̂�


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

long Speed_control::control(char reference_speed , unsigned char brake_mode)
{
	
	char motor_num;
	char port;
	
	port = port_num;//�����o�ϐ�������
	motor_num = Motor_num;//�����o�ϐ�������
	
	
//�ϐ�
	unsigned char Mode;//���[�^1���x����ݒ胂�[�h
	
	unsigned char Rx_data[9];
	
	unsigned char mark_data = 0;	
    long encoder_data = 0;
    long moter_rpm = 0;


	if(reference_speed < 0)
	{
		mark_data = 0b00000001;
		reference_speed *= -1;
	}

//�ڕW�l���e���M
	if(motor_num == 1){
		Mode = 5;
		
		Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
		Dlno_Serial_write(Mode,port);//���[�h
		Dlno_Serial_write(reference_speed ,port);
		Dlno_Serial_write(1,port);
		Dlno_Serial_write(mark_data,port);
		Dlno_Serial_write(brake_mode ,port);
		Dlno_Serial_write(1,port);
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(250,port);//�G���h�o�C�g
	}
	
	else if(motor_num == 2){
		Mode = 6;
		
		Dlno_Serial_write(200,port);//�X�^�[�g�o�C�g
		Dlno_Serial_write(Mode,port);//���[�h
		Dlno_Serial_write(1,port);
		Dlno_Serial_write( reference_speed,port );
		Dlno_Serial_write( mark_data,port );
		Dlno_Serial_write(1 ,port);
		Dlno_Serial_write(brake_mode,port);
	    Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(1,port); //�_�~�[
		Dlno_Serial_write(250,port);//�G���h�o�C�g
	}
		
		//�f�[�^��M
	
	Dlno_dataReceive(10,Rx_data,port);
//��M�f�[�^����
moter_rpm = ((long)Rx_data[0] <<24) + ((long)Rx_data[1] <<16) + ((long)Rx_data[2] << 8) + ((long)Rx_data[3]);
encoder_data = ((long)Rx_data[4] <<24) + ((long)Rx_data[5] <<16) + ((long)Rx_data[6] << 8) + ((long)Rx_data[7]);

return moter_rpm;
}

//�E���[�^�[���Ɋ֐��𕪂��������悢�̂�



