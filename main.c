#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h> //delay header
#include <stdio.h>
#include <stdlib.h>
#include <avr/interrupt.h>

#define LCD_DPRT PORTD //LCD DATA PORT
#define LCD_DDDR DDRD //LCD DATA DDR
#define LCD_CPRT PORTA //LCD COMMANDS PORT
#define LCD_CDDR DDRA //LCD COMMANDS DDR

#define LCD_RS 0
#define LCD_EN 2

#define IR1 0
#define IR2 1


void lcdCommand( unsigned char cmnd )
{
	LCD_DPRT = cmnd;
	LCD_CPRT &= ~ ((1<<LCD_RS)); //RS = 0
	LCD_CPRT |= (1<<LCD_EN); //EN = 1
	_delay_us(100);
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100);
}
void lcdData( unsigned char data )
{
	LCD_DPRT = data; //send data
	
	LCD_CPRT |= ((1<<LCD_RS)|(1<<LCD_EN)); //RS = 1 for data //EN = 1
	_delay_us(100);
	LCD_CPRT &= ~ (1<<LCD_EN); //EN = 0 for H-to-L pulse
	_delay_us(100);
}

void lcd_init()
{
	LCD_DDDR = 0xFF;
	LCD_CDDR = 0xFF;
	LCD_CPRT &=~(1<<LCD_EN); //LCD_EN = 0
	_delay_us(2000);
	lcdCommand(0x38); //init. LCD 2 line, 5 × 7 matrix
	lcdCommand(0x0E); //display on, cursor on
	lcdCommand(0x01); //clear LCD
	_delay_us(2000);
	lcdCommand(0x06); //shift cursor right
}
void lcd_print(char *str)
{
	
	unsigned int i=0;
	while(str[i]!='\0')
	{
		lcdData(str[i++]);
	}
}

void Timer1_CTC_init()
{
	OCR1A = 15625;
	TIMSK = (1<<OCIE1A);
	TCCR1A = 0;
	TCCR1B = 11;
}
long seconds=0;
ISR(TIMER1_COMPA_vect)
{
	seconds++;
}

void t1()
{
	PORTB=0X01;
	TCCR1A=0X0;
	TCCR1B=0X06;
	TCNT1H=0X0;
	TCNT1L=0X0;
}

int main(void)
{
	
	lcd_init();
	lcd_print("    WELCOME    ");
	_delay_ms(200);
	lcdCommand(0x01);
	lcd_print(" Speed detector ");
	_delay_ms(400);
	lcdCommand(0x01);
	lcdCommand(0x81);
	lcd_print(" Safe speed ");
	lcdCommand(0xc3);
	lcd_print(" = 130 km/s ");
	
	Timer1_CTC_init();
	sei();
	
	int count1=0x0,count2=0x0,b1=0,b2=0;
	int ad=0x30,i=0;
	DDRC=0x0;
	
	
	while(1)
	{
		PORTD=0;
		if((PINC)==(1<<IR1) && b1!=1) //To make sure IR1 is not detected twice
		{
			lcdCommand(0x01);
			lcdCommand(0x81);
			lcd_print(" IR1 detected");
			TCNT1=0;
			b1++;
		}
		if((PINC)==(1<<IR2)  && b2!=1)  //To make sure IR1 is not detected twice
		{
			lcdCommand(0x81);
			lcd_print(" IR2 detected");
			count2=seconds;
			b2++;
		}
		if(b1==1 && b2==1) //If both IR sensors have detected the vehicle then break the loop
		break;
	}
	
	float time=count2*1.0; // 
	float distance=20.0,conv=36.0; //The distance between the IR sensors is 20m 
	float sp=distance/time;
	sp=(sp*conv);
	
	_delay_ms(500);
	int isp=ceil(sp);
	int comp=isp;
	char ssp[5];
	lcdCommand(0x01);
	lcdCommand(0x80);
	lcd_print(" Speed recorded ");
	lcdCommand(0xc4);
	itoa(isp,ssp,10); //converting the speed to a string 
	lcd_print(ssp);
	lcd_print(" km/hr ");
	
	if(comp>130) //Check if the speed of the vehicle is over 130kmph
	{
		_delay_ms(500);
		lcdCommand(0x01);
		lcdCommand(0x80);
		lcd_print(" Over speeding");
		lcdCommand(0xc0);
		lcd_print(" Maintain speed ");
	}
	lcdCommand(0x01);
	lcdCommand(0x82);
	lcd_print(" Thank you");
	
	return 0;
}
