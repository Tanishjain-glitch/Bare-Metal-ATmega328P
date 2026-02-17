#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t timer_count = 0;
volatile uint8_t send_flag = 0;

// Timer1 Compare Match A interrupt
ISR(TIMER1_COMPA_vect)
{
    timer_count++;
    
    // Set flag every 1000ms (1000 interrupts at 1ms each)
    if (timer_count >= 1000) {
        send_flag = 1;
        timer_count = 0;
    }
}

void timer_init()
{
    // CTC mode
    TCCR1B |= (1 << WGM12);
    
    // Prescaler = 64
    TCCR1B |= (1 << CS11) | (1 << CS10);
    
    // 1ms tick
    OCR1A = 249;
    
    // compare interrupt
    TIMSK1 |= (1 << OCIE1A);
    
    //global interrupts
    sei();
}

void uart_init()
{
    // Set baud rate 103 = 9600 baud Ref Page 165
    UBRR0 = 103;                           //U2X0 = 0
    
    // Enable transmitter
    UCSR0B = (1 << TXEN0); //tx
    
    // 8 data bits, no parity, 1 stop bit
    UCSR0B &= ~(1<<UCSZ02);                        //0
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);        // 1 1 pg 162
}

void uart_char(char c)
{
    // Wait
    while (!(UCSR0A & (1 << UDRE0)));
    
    UDR0 = c;
}

void uart_string(const char *str)
{
    while (*str) {
        uart_char(*str++);
    }
}

int main(void)
{
    uart_init();
    timer_init();
    
    while (1) 
    {
        if (send_flag) {
            uart_string("Hello from UART\r\n");
            send_flag = 0;
        }
    }
    
    return 0;
}
