# SoftwarePWM
This lab focuses on implementing pulse width modulation with timers. This is done by utilizing the CCR registers which can be set up to behave like a duty cycle. To implement this correctly one timer uses a CCR0 of 100 which is our effective percentage. Now any ccr value under 100 will give a percent of the total period on which gives pulse width modulation. A button is then added to increase the duty cycle in intervals of 10%. Once it hits 100% the duty cycle resets to zero. A second led is toggled every time the button is pressed.

## Boards Implemented On:
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Differences On Boards
### MSP430F5529
P2.1 is used for the button. P1.0 is the LED toggled when the button is pressed. P4.7 was used as the led representing the button press. TimerA0 was used to prevent bouncing. TimerA1 was used to generate the PWM signal for the LED.

### MSP430FR2311
P1.1 is used for the button. P1.0 is the led which is being affected by the pulse width modulation. P2.0 is the LED toggled when button is pressed. TimerB0 was used to prevent the button bouncing. TimerB1 was used to generate the PWM signal to put to the led.

### MSP430FR5994
P5.6 is used for the button. P1.0 is the LED being manipulated by the PWM. P1.1 is the led which is toggled when button is pressed. TimerA0 was used to prevent button bouncing. TimerA1 was used to generate the PWM signal for the LED.

### MSP430FR6989
P1.1 is used for the button. P1.0 is the LED controlled by PWM signal. P9.7 is the LED which toggles when the button is pressed. TimerA0 was used to prevent bouncing. TimerA1 was used to generate the PWM signal for the LED.

### MSP430G2553
P1.3 is used for the button. P1.0 is the LED with the PWM signal. P1.6 is the LED which toggles everytime the button is actuated. TimerA0 was used to prevent button bouncing. TimerA1 was used to generate the signal for the LED.

