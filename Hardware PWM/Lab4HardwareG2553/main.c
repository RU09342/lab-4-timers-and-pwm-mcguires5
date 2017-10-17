// Loads configurations for all MSP430 boards
#include <msp430.h>

volatile int duty = 10; // duty cycle initialized at 50%

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer

    // Disables default high-impedance mode

    // Button configuration
    P1DIR = BIT0; // Set P1.0 as output
    P1DIR = BIT6; // Set P2.0 as output
    P1SEL |= BIT6; //Tie pin to peripheral not gpio
    P1REN |= BIT3; // Connects the on-board resistor to P1.1
    P1OUT = BIT3; // Sets up P1.1 as pull-up resistor

    // Interrupt Configuration
    P1IES |= BIT3; // Interrupts on rising Edge
    P1IE |= BIT3; // Enable interrupt on button pin
    P1IFG &= ~BIT3; // Clear interrupt flag

    TA0CCR0 = 0x5FFF;
    TA0CCTL0 = CCIE; // B0 CC interrupt enable

    //timerB1 used to generate PWM
    // Duty cycle timer set to 100 so percents can be used directly
    TA1CCTL1 = OUTMOD_7;
    TA1CCR0 = 100;
    TA1CCR1 = duty; //initialize to 50% duty cycle
    TA1CTL = TASSEL_2 + MC_1 + TACLR;  //SMCLCK UPMODE Clear


    __enable_interrupt(); // Enables all interrupts
    __bis_SR_register(GIE); // enable global interrupts


}


//Button Press Interupt
#pragma vector = PORT1_VECTOR
__interrupt void PORT_1(void)
{
    //If interrupt edge is positive it is first time
    if((P1IES & BIT3) == BIT3){
        if(TA1CCR1 >= 100) {
            TA1CCR1 = 0;
        }else{
            TA1CCR1 = TA1CCR1 + 10;
        }
        P1OUT ^= BIT0; // Toggle 2nd LED
        TA0CTL = TASSEL_2 + MC_1 + ID_3; //SMCLK with up mode divider of 8 (Starts debounce timer)
        TA0R = 0; //Reset the value counting from
        P1IES &= ~BIT3; // Set interrupt edge to falling edge
        P1IFG &= ~BIT3; //turns off button inturrupt flag
        P1IE &= ~BIT3;  // Disable interrupts to prevent bounce
    }else{ //if interrupt edge is negative then falling edge
        P1OUT ^= BIT0; // Blink 2nd LED
        P1IFG &= ~BIT3; //turns off button inturrupt flag
        P1IES |= BIT3; // Set Interrupt edge to rising edge
        P1IE |= BIT3;  // enables interrupts
    }
    //SMCLK as clock source + MC_1 Count-up mode


    P1IFG &= ~BIT3;   // Clear P1.1 interrupt flag


}

// Interrupt subroutine
// Called when timer reaches TB0CCR0
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
    P1IE |= BIT3;  //Enable interrupts on the button
    TA0CTL &= ~ TASSEL_2; // Stop TimerB0
    TA0R = 0; //Clears value of timer

}
