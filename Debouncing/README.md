# Software Debouncing
This lab focuses on debouncing a button. This can be done by simply delaying the processor until the signal stops bouncing, but this would render our processor useless in the waiting period. To avoid this downtime we will use timers and interupts to tell the processor when to disable the button interupts and then when to reenable the interupts. When looking at a button press on an oscilliscope the time of bounce did not exceed 10 ms so that would be a safe amount of time to set the timer module for. SMCLK about equals 1.25 MHz with a clock divider of 8 1250000/8 = 156250/0x00FF = .0016 or about 1.6 ms

## Boards Implemented On:
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

## Differences On Boards
### MSP430F5529
P2.1 is used for the button. P1.0 is the LED toggled when the button is pressed. TimerB0 was used to time the debouncing.

### MSP430FR2311
P1.1 is used for the button. P1.0 is the LED toggled when button is pressed. TimerB0 was used to time the debouncing.

### MSP430FR5994
P5.6 is used for the button. P1.0 is the LED toggled when button is pressed. TimerA0 was used to time the debouncing.

### MSP430FR6989
P1.1 is used for the button. P1.0 is the LED toggled when button is pressed. TimerA0 was used to time the debouncing.

### MSP430G2553
P1.3 is used for the button. P1.0 is the LED toggled when the button is pressed. TimerA0 was used to time the debouncing.


