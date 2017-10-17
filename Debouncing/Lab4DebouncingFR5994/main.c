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
    P5IE |= (BIT6);       //Enables interrupts for P1 Bit 1
    P5IES |= BIT6;
    P5REN |= (BIT6);    //Enables the resistor for P1 Bit 1
    P5OUT |= (BIT6);
    P5OUT |= (BIT6);//Sets the resistor for P1 Bit 1 to Pull Up
    P5IFG &= ~BIT6;   //The interrupt flag is cleared


    //enable all interrupts
    __bis_SR_register(GIE); // LPM0 with interrupts enabled

}


// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR (void)
{
        P5IE |= BIT6;

}


//Port 1 interrupt service routine
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
{
    P1OUT ^= BIT0;

    P5IFG &= ~BIT6;
    if((P5IES & BIT6) == BIT6){
        TA0CCTL0 = CCIE;
        P5IE &= ~BIT6;
        P5IES &= ~BIT6;
        TA0CTL |= MC_1;
        TA0R = 0;
        P5IFG &= ~BIT6;
    }else{
        TA0CCTL0 = ~CCIE;
    }


}
