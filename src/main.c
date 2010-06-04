#define F_CPU F_OSC
#include <avr/io.h>
#include <util/delay.h>
#include "bla.h"

#define sbi(port, bit) (port) |= (1 << (bit))
#define cbi(port, bit) (port) &= ~(1 << (bit))

#define RS PB3
#define RW PB1
#define EN PB0

void lcd_enable(void)
{
	PORTB |= _BV(EN);
	_delay_us(1);                   // kurze Pause
	PORTB &= ~(_BV(EN));
}


// sendet einen Befehl an das LCD
 
void lcd_command(unsigned char temp1)
{
	unsigned char temp2 = temp1;
	
	PORTB &= ~(_BV(RS));        // RS auf 0 setzen
	
	//temp1 = temp1 >> 4;              // oberes Nibble holen
	//temp1 = temp1 & 0x0F;            // maskieren
	
	//temp1 <<= 4;
	temp1 &= 0xf0;
	
	//LCD_PORT &= 0xF0;
	PORTA = temp1;
	//LCD_PORT |= temp1;               // setzen
	lcd_enable();
	
	//temp2 = temp2 & 0x0F;            // unteres Nibble holen und maskieren
	temp2 <<= 4;
	temp2 &= 0xf0;
	//LCD_PORT &= 0xF0;
	//LCD_PORT |= temp2;               // setzen
	PORTA = temp2;
	lcd_enable();
	
	_delay_us(80);
}

void lcd_data(unsigned char temp1)
{
	unsigned char temp2 = temp1;
	
	PORTB |= _BV(RS);        // RS auf 0 setzen
	
	//temp1 = temp1 >> 4;              // oberes Nibble holen
	//temp1 = temp1 & 0x0F;            // maskieren
	
	//temp1 <<= 4;
	temp1 &= 0xf0;
	
	//LCD_PORT &= 0xF0;
	PORTA = temp1;
	//LCD_PORT |= temp1;               // setzen
	lcd_enable();
	
	//temp2 = temp2 & 0x0F;            // unteres Nibble holen und maskieren
	temp2 <<= 4;
	temp2 &= 0xf0;
	//LCD_PORT &= 0xF0;
	//LCD_PORT |= temp2;               // setzen
	PORTA = temp2;
	lcd_enable();
	
	_delay_us(80);
}


int main(void)
{
	_delay_ms(45);
	DDRA = 0xff;
	DDRB |= (_BV(EN) | _BV(RW) | _BV(RS));
	DDRD = _BV(PD6);
	_delay_ms(15);
	
	PORTB &= ~(_BV(RW));
	
	PORTA = (_BV(PA4) | _BV(PA5));   //DB4/DB5 setzen, Rest 0
	
	lcd_enable();	  //Enable schaltet Ausgänge an LCD durch
	
	_delay_ms(5);
	lcd_enable();	//gleichen Code nochmal
	_delay_ms(5);
	lcd_enable();
	
	// 4 Bit Modus aktivieren 
	PORTA = _BV(PA5);
	lcd_enable();
	_delay_ms(1);
	
	//Function Set --> S. 49,
	// 4Bit / 2 Zeilen / 5x7
	
	lcd_command(0x28);
	
	// Display ein / Cursor aus / kein Blinken
	lcd_command(0x0D); 
	
	//Display clear
	
	//lcd_clear();
	lcd_command(0x01);
	
	// inkrement / kein Scrollen
	
	lcd_command(0x06);
	
	lcd_command(0x40 + _BV(7));
	
	//lcd_data('a');
	
	while(1)
	{
		sbi(PORTD, PD6);
		_delay_ms(200);
		cbi(PORTD, PD6);
		_delay_ms(200);
	}
	
	return 0;
}

