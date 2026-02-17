#include <avr/io.h>

void setup_gpio()
{
    // Pin 13 (PB5) as output
    DDRB = DDRB | (1 << 5);
}

void toggle_led()
{
    PORTB = PORTB ^ (1 << 5);  // XOR to toggle
}

void delay_500ms(void) {
    for (volatile unsigned long i = 0; i < 200000; i++);  // ~500ms
}

int main(void)
{
    setup_gpio();
    
    while (1) 
    {
        toggle_led();
        delay_500ms();
    }
    
    return 0;
}
