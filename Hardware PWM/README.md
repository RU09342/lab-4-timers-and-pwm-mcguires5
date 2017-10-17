# HardwarePWM
This lab focuses on implementing pulse width modulation with the set reset mode for the timer. This will allow us to create a duty cycle and output it directly to an led. In this lab we use OUTMOD_7 as it is the set reset of the CCR registers.

## Boards Implemented On:
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Differences On Boards
### MSP430F5529
P2.1 is used for the button. P4.7 is the LED manipulated by the PWM signal. P1.0 was used as the led representing the button press. TimerA0 was used to prevent bouncing. TimerA1 was used with OUTMOD_7 to generate the PWM signal for the LED.

### MSP430FR2311
P1.1 is used for the button. P2.0 is the led which is being affected by the pulse width modulation. P1.0 is the LED toggled when button is pressed. TimerB0 was used to prevent the button bouncing. TimerB1 was used with OUTMOD_7 to generate the PWM signal to put to the led.

### MSP430FR5994
P5.6 is used for the button. P1.1 is the LED being manipulated by the PWM. P1.0 is the led which is toggled when button is pressed. TimerA0 was used to prevent button bouncing. TimerA1 was used with OUTMOD_7 to generate the PWM signal for the LED.

### MSP430FR6989
P1.1 is used for the button. P9.7 is the LED controlled by PWM signal. P1.0 is the LED which toggles when the button is pressed. TimerA0 was used to prevent bouncing. TimerA1 with OUTMOD_7 was used to generate the PWM signal for the LED.

### MSP430G2553
P1.3 is used for the button. P1.6 is the LED with the PWM signal. P1.0 is the LED which toggles everytime the button is actuated. TimerA0 was used to prevent button bouncing. TimerA1 with OUTMOD_7 was used to generate the signal for the LED.

