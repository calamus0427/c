#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define water D0
sbit water=P3^0;
sbit EN=P2^7;
sbit RS=P2^6;
sbit RW=P2^5;
sbit dula=P2^6;
sbit wela=P2^7;
sbit key1=P3^1;
sbit key2=P3^2;
sbit RELAY=P3^3;
sbit led1=P2^1;
sbit led2=P2^2;
uchar code watering[]="I want watering!";
uchar code fine[]="I am very fine!!";
uchar code chat[]=" Chat with me~  ";
uchar code message[]="    message     ";
uchar num;
uint x;

void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void write_com(uchar com)
{
	RS=0;
	P0=com;
	delayms(5);
	EN=1;
	delayms(5);
	EN=0;	
}

void write_data(uchar date)
{
	RS=1;
	P0=date;
	delayms(5);
	EN=1;
	delayms(5);
	EN=0;
}

void init()
{
	RW=0;
	EN=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}


uint keyscan(void)
{
	static uint a;
	if(key1==0 || key2==0)	
	{
	//	led1=0;
	//	led2=0;
	delayms(2);   		    //20毫秒软件消抖
		if(key1 == 0)
		{ 
			a=0;
			led1=1;
			led2=0;		
		}
		else if(key2 == 0)
		{			
			a=1;
			led2=1;
			led1=0;
		}
	}
	else
	{
		led1=0;
		led2=0;
	}
	return a;	
}

void autowater()
{
	if(water)
			{
				RELAY = 0; //继电器闭合
				write_com(0x80);
				for(num=0;num<16;num++)
				{
					write_data(watering[num]);
					delayms(5);
				}
			}			
			else
			{
				RELAY=1;
				write_com(0x80);
				for(num=0;num<16;num++)
				{
					write_data(fine[num]);
					delayms(5);
				}	
			}  
}

void gsmwater()      /*gsm控制模块,需要改动*/
{
	if(water)
			{
				RELAY = 0; //继电器闭合
				write_com(0x80);
				for(num=0;num<16;num++)
				{
					write_data(message[num]);
					delayms(5);
				}
			}			
			else
			{
				RELAY=1;
				write_com(0x80);
				for(num=0;num<16;num++)
				{
					write_data(chat[num]);
					delayms(5);
				}	
			}  		
}



void display()
{	
	x=keyscan();
	switch(x)
		{
			case 0:
				autowater();
				break;
			case 1:
				gsmwater();
				break;
		}	
}	
