#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define speed 110
#define water D0
			     

void delay(int time);
void Go();

void delayms(uint xms);
void write_com(uchar com);
void write_data(uchar date);
void init();
uint keyscan(void);
void display();
