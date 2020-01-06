#define F_CPU 1000000UL
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define k_prt PORTC
#define k_ddr DDRC
#define k_pin PINC


int get_num(char ch)
{
	switch(ch)
	{case'0':return 0;break;
		case'1':return 1;break;
		case'2':return 2;break;
		case'3':return 3;break;
		case'4':return 4;break;
		case'5':return 5;break;
		case'6':return 6;break;
		case'7':return 7;break;
		case'8':return 8;break;
	case'9':return 9;break;	}
	return 0;
}

//calculator function
unsigned char get_character(int number )
{
	switch(number)
	{ case 0 :return '0';break;
		case 1 :return '1';break;
		case 2 :return '3';break;
		case 4 :return '4';break;
		case 5 :return '5';break;
		case 6 :return '6';break;
		case 7 :return '7';break;
		case 8 :return '8';break;
	case 9 :return '9';break;	}return 0;
}
char return_ASCII(char symbol)
{
	if(symbol=='0')
	return 0x48;
	if(symbol=='1')
	return 0x49;
	if(symbol=='2')
	return 0x50;
	if(symbol=='3')
	return 0x51;
	if(symbol=='4')
	return 0x52;
	if(symbol=='5')
	return 0x53;
	if(symbol=='6')
	return 0x54;
	if(symbol=='7')
	return 0x55;
	if(symbol=='8')
	return 0x56;
	if(symbol=='9')
	return 0x57;
	if(symbol=='=')
	return 0x61;
	if(symbol=='+')
	return 0x43;
	if(symbol=='-')
	return 0x45;
	if(symbol=='*')
	return 0x42;
	return 0;
}

void delay_ms(unsigned int d)
{
	_delay_ms(d);
}
char *pass[8]=
{
	"1000","2000",
	"3000","4000",
	"5000","6000",
	"7000","8000"
};
unsigned char keypad[4][4]=
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'o','0','=','+'}
};
unsigned char rowloc,colloc;
void func()
{
	k_ddr=0xf0;
	k_prt=0xff;
	
	do
	{
		k_prt &= 0x0f;
		colloc=(k_pin & 0x0f);
		if(PINB==0x01)
		PORTD |= (0X01);
		if(PINB==0x02)
		PORTD |= (0X02);
		if(PINB==0x04)
		PORTD |= (0X04);
		if(PINB==0x08)
		PORTD |= (0X08);
		if(PINB==0x10)
		PORTD |= (0X10);
		if(PINB==0x20)
		PORTD |= (0X20);
		if(PINB==0x40)
		PORTD |= (0X40);
		if(PINB==0x80)
		PORTD |= (0X80);
		if(PINB==0x00)
		PORTD=0X00;
	} while (colloc!=0x0f);
	do
	{
		delay_ms(20);
		colloc=(k_pin & 0x0f);
		if(PINB==0x01)
		PORTD |= (0X01);
		if(PINB==0x02)
		PORTD |= (0X02);
		if(PINB==0x04)
		PORTD |= (0X04);
		if(PINB==0x08)
		PORTD |= (0X08);
		if(PINB==0x10)
		PORTD |= (0X10);
		if(PINB==0x20)
		PORTD |= (0X20);
		if(PINB==0x40)
		PORTD |= (0X40);
		if(PINB==0x80)
		PORTD |= (0X80);
		if(PINB==0x00)
		PORTD=0X00;
	} while (colloc==0x0f);
	while(1)
	{
		k_prt=0xef;
		colloc=(k_pin & 0x0f);
		if(colloc != 0x0f)
		{
			rowloc=0;
			break;
		}
		k_prt=0xdf;
		colloc=(k_pin & 0x0f);
		if(colloc != 0x0f)
		{
			rowloc=1;
			break;
		}
		k_prt=0xbf;
		colloc=(k_pin & 0x0f);
		if(colloc != 0x0f)
		{
			rowloc=2;
			break;
		}
		k_prt=0x7f;
		colloc=(k_pin & 0x0f);
		if(colloc != 0x0f)
		{
			rowloc=3;
			break;
		}
		
	}
	
}
int col()
{
	if(colloc==0x0e)
	return 0;
	if(colloc==0x0d)
	return 1;
	if(colloc==0x0b)
	return 2;
	if(colloc==0x07)
	return 3;
	return 0;
}
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	
	//int a=-1,b=-1;
	//char what='-';
	DDRD =  0xff;//for leds ... when door is open , led will be turned on 
	DDRB=0x00;//for switches when s-o wants to open the door from inside
	//PORTB=0x00;
	//lcdgotoxy(1,1);
	k_ddr=0xf0;
	k_prt=0xff;
	unsigned char row,column;
	while (1)
	{
		
		func();
		
		if(colloc==0x0e)
		{
			row=rowloc;
			column=col();
			//PORTD=(0x01);
			char r[5];
			int i=0;
			while(1)
			{
				func();
				
				colloc=col();
				//PORTD=rowloc;
				if(keypad[rowloc][colloc]=='o')
					break;
				r[i]=keypad[rowloc][colloc];
				i+=1;
			}
			r[i]='\0';
			if(strstr(r,pass[get_num(keypad[row][column])-1]))
			PORTD |= (1<<(get_num(keypad[row][0])-1));
			delay_ms(1000);
			PORTD &= 0x00;
		}
		else if (colloc==0x0d)
		{
			char r[5];
			row=rowloc;
			column=col();
			//PORTD=column;
			int i=0;
			while(1)
			{
				func();
				colloc=col();
				//PORTD=rowloc;
				if(keypad[rowloc][colloc]=='o')
				break;
				r[i]=keypad[rowloc][colloc];
				i+=1;
			}
			r[i]='\0';
			
			if(strstr(r,pass[get_num(keypad[row][column])-1]))
			PORTD |= (1<<(get_num(keypad[row][1])-1));
			delay_ms(1000);
			PORTD &= 0x00;
		}
		
		else if (colloc==0x0b)
		{
			char r[5];
			int i=0;
			row=rowloc;
			column=col();
			while(1)
			{
				func();
				colloc=col();
				//PORTD=rowloc;
				if(keypad[rowloc][colloc]=='o')
				break;
				r[i]=keypad[rowloc][colloc];
				i+=1;
			}
			r[i]='\0';
			
			if(strstr(r,pass[get_num(keypad[row][column])-1]))
			PORTD |= (1<<(get_num(keypad[row][2])-1));
			delay_ms(1000);
			PORTD &= 0x00;
			
		}
		
	}
	/*{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'on','0','=','+'}*/
	//board_init();
	return 0;
	/* Insert application code here, after the board has been initialized. */
}

