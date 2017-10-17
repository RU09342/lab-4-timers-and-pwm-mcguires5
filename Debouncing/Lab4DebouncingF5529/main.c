#include <msp430.h> 


/**
 * main.c
 */
#include <msp430.h>

//TIMER
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= (BIT0 + BIT6);
    P1OUT &= 0x00; // Set the LEDs off
                   // CCR0 interrupt enabled
    TB0CTL = TBSSEL_2 + MC_0 + ID_3;           // SMCLK/8, upmode

    TB0CCR0 =  0x00FF;  //1250000/8 = 156250/0x05FF = .009 or about 10 ms
    TB0CCTL0 &= ~CCIE;
    P1DIR |= (BIT0);
    P1DIR |= (BIT0);
    P1OUT |= (BIT0);
    P2IE |= (BIT1);       //Enables interrupts for P1 Bit 1
    P2IES |= BIT1;
    P2REN |= (BIT1);    //Enables the resistor for P1 Bit 1
    P2OUT |= (0x03);
    P2OUT |= (BIT1);//Sets the resistor for P1 Bit 1 to Pull Up
    P2IFG &= ~BIT1;   //The interrupt flag is cleared


    //enable all interrupts
    __bis_SR_register(GIE); // LPM0 with interrupts enabled

}


// Timer A0 interrupt service routine
#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMER0_B0_ISR (void)
{
        P2IE |= BIT1;

}


//Port 1 interrupt service routine
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    P1OUT ^= BIT0;

    P2IFG &= ~BIT1;
    if((P2IES & BIT1) == BIT1){
        TB0CCTL0 = CCIE;
        P2IE &= ~BIT1;
        P2IES &= ~BIT1;
        TB0CTL |= MC_1;
        TB0R = 0;
        P2IFG &= ~BIT1;
    }else{
        TB0CCTL0 = ~CCIE;
    }


}
