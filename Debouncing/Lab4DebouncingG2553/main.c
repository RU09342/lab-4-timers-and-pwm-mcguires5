#include <msp430.h> 


/**
 * main.c
 */
#include <msp430.h>

//TIMER
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR |= (BIT0 + BIT6);
    P1OUT &= 0x00; // Set the LEDs off
                   // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + MC_0 + ID_3;           // SMCLK/8, upmode

    TA0CCR0 =  0x00FF;  //1250000/8 = 156250/0x00FF = .0016 or about 1.6 ms
    TA0CCTL0 &= ~CCIE;
    P1DIR |= (BIT0);
    P1DIR |= (BIT0);
    P1OUT |= (BIT0);
    P1IE |= (BIT3);       //Enables interrupts for P1 Bit 1
    P1IES |= BIT3;
    P1REN |= (BIT3);    //Enables the resistor for P1 Bit 1
    P1OUT |= (BIT3);
    P1OUT |= (BIT3);//Sets the resistor for P1 Bit 1 to Pull Up
    P1IFG &= ~BIT3;   //The interrupt flag is cleared


    //enable all interrupts
    __bis_SR_register(GIE); // LPM0 with interrupts enabled

}


// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
        P1IE |= BIT3;

}


//Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    P1OUT ^= BIT0;

    P1IFG &= ~BIT3;
    if((P1IES & BIT3) == BIT3){
        TA0CCTL0 = CCIE;
        P1IE &= ~BIT3;
        P1IES &= ~BIT3;
        TA0CTL |= MC_1;
        TA0R = 0;
        P1IFG &= ~BIT3;
    }else{
        TA0CCTL0 = ~CCIE;
    }


}
