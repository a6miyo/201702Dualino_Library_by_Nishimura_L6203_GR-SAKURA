/////////////////////////////////////////////////////////////////
//Dlno_dataReceive.c
//山形大学  山野研究室
//八鍬  一史
//////////////////////////////////////////////////////////////////


#include "Dlno_dataReceive.h"

void Dlno_dataReceive(char bytesize,unsigned char data[],char num)
{	
	unsigned char Rx_data_new = 0;
	unsigned char count = 0;
	unsigned char Rx_comp_flag = 0;
	
	while(Rx_comp_flag == 0)
	{ 	
	
	  if(Dlno_Serial_available(num) > 0)//受信バッファにデータがあるかチェック
	  {
	        Rx_data_new = Dlno_Serial_read(num); //データ受信
	  	  // 	Serial.println(Rx_data_new);
		//Serial.println("2");

	  	
	        if(count == 0) //count値が0,もしくはそれ以下の場合
	        {
	        	if(Rx_data_new == 200){ count++;//スタートバイト(200)が送られてきたとき
		//Serial.println("3");
	        	}
	        	else{ count = 0;                 //スタートバイト(200)ではないときカウント初期化
		//Serial.println("4");
	        	}
	        }
	        else if(count > 0)//count値が0以上の場合
	        {   
		//Serial.print("5 = ");
		//Serial.println(Rx_data_new);
	            data[(count - 1)] = Rx_data_new; //配列 Rx_data[]に データ保存
	            
	            count++;
	          
	        	if( count >= bytesize) //coun値がエンドバイトが送られてくるであろうバイト数に達した時
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
	
	  if(Dlno_Serial_available(num) > 0)//受信バッファにデータがあるかチェック
	  {
	        Rx_data_new = Dlno_Serial_read(num); //データ受信
	  	    int a = Rx_data_new;
	  		Serial.println(a);
	  }

	}
	}	

  */ 