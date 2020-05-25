
/*
The code to generate a PWM signal with frequency 100Hz and duty cycle of 70%.
F=100Hz --> T=10ms
Pre-scaler 1024 @16MHz --> tick=0,064ms
T_PWM = 0,064ms * 156 = 10 ms --> OCR0A = 156-1 = 155
Duty_cycle = 70% --> 0.7 * 155 --> OCR0B = 108
*/

#include <avr/interrupt.h>
#include <avr/io.h>

ISR(TIMER0_COMPB_vect) { //Clear PB0, meaning PB='0'
    PORTB &= ~(1 << PB0);
}
ISR(TIMER0_COMPA_vect) {
    //Assert PB0, meaning PB='1'
    PORTB |= 1 << PB0;
}
int main() {
    // Set PB0 as output
    // This pin the pin providing PWM
    DDRB |= (1 << PB0);
    OCR0A = 155; //PWM period
    OCR0B = 108; //PWM duty cycle
    // Set CTC Mode (Mode 2-Table 15-8)
    TCCR0A |= 1 << WGM01;
    // Enable interrupts COMPA and COMPB
    TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B);
    sei();
    TCNT0 = 0x00;
    // Set Pre-scaler to 1024 and start the timer
    TCCR0B |= (1 << CS00) | (1 << CS02);
    while (1) {
    }
}
