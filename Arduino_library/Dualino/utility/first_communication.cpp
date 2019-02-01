#include"first_communication.h"

void first_comunication(char port);


void first_com(char port){

 static char first_com_flag[4] = {0};
 
 switch(port)
 {
 case 0:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 case 1:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 case 2:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 case 3:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break; 
 case 4:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 case 5:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 case 6:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 case 7:
 	if(first_com_flag[port]==0)first_comunication(port);
 	first_com_flag[port] = 1;
 	break;
 default:
 	break;
 	
 }


	
}

void first_comunication(char port){
 unsigned long time_now = 0;
 unsigned long time_zero = 0;
 
 int first_Rx_comp_flag = 0;
 int count = 0;
 int receive_data = 0;
 
	
 Dlno_Serial_begin(38400,port);//38400,161024
//	delay(2900);//無効,1000
/*
 Dlno_Serial_write(200,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(1,port);
 delay(1);
 Dlno_Serial_write(250,port);
delay(1);
*/
	
	
 Dlno_Serial_write(200,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(1,port);
 Dlno_Serial_write(250,port);


Serial.println("send_data");
 time_zero = millis();

    
   

while(first_Rx_comp_flag == 0){    

		 time_now = millis();
		 time_now -= time_zero;

		    if(time_now > 6000)  //この関数を呼んだあと3秒以上応答がなければ動作停止
		    {
		        while(1){
		           delay(1000);
		        	Serial.println("stop");
		        }    
		    }
			
			 if(Dlno_Serial_available(port) > 0)
		    {
		        receive_data = Dlno_Serial_read(port); //startbyte check
		       // Serial.println("1");
		        //Dlno_Serial_println(receive_data);
		      // Serial.println(receive_data);
						
		        if(count<= 0)
		        {
		        	//Serial.println("2-1");
		              if(receive_data == 200)
		              {
		              	//Serial.println("3-1");
		                  count++;
		              }
		              else
		              {
		              	//Serial.println("3-2");
		                  count = 0;
		              }
		              
		        }
		        else
		        {
		        	//Serial.println("2-2");
		            count++;
		            if( count >=10)
		            {
		            	//Serial.println("4-1");
		                if(receive_data == 250)
		                {
		                	//Serial.println("5");
		                    first_Rx_comp_flag = 1;
		                }
		                else
		                {
		                	//Serial.println("4-2");
		                    first_Rx_comp_flag = 0;
		                    count = 0;
		                }
		               
		            }
		        }
		   }    
		} 
			delay(300);
		
	
    
}


