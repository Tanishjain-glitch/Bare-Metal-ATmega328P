#include <avr/io.h>

void uart_init()
{
    // baud rate (103 = 9600)// Available in DATASHEET REF PAGE no 165
    UBRR0L = 103;
    
    // Enable tx
    UCSR0B = (1 << TXEN0);
    
    // 8 data bits, no parity, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
}

void uart_char(char c)
{
    // Wait
    while (!(UCSR0A & (1 << UDRE0)));
    
    UDR0 = c;  // Send char
}

void uart_string(const char *str)
{
    while (*str) {
        uart_char(*str++);
    }
}

void delay_sec(void) {
    // Rough 1 second delay (tested on hardware) TIMERS can be also used
    for (volatile unsigned long i = 0; i < 400000; i++);
}


void setup()
{
  
    uart_init();
}

void loop()
{
  
    uart_string("Hello from UART\r\n");
    delay_sec();
    
}
