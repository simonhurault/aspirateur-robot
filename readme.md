# Automatic aspirator

This project refers to the S5 polytech project. The objective is to create an automatic aspirator.


## Table of Contents

  * [Requirements](#requirements)
  * [Usage](#usage)
  * [License](#license)


## Requirements

This project requires the following to run:

  * [Arduino](https://www.arduino.cc/)
  * [Arduino motor shield REV3](https://store.arduino.cc/arduino-motor-shield-rev3)
  * [Arduino HC-SC04 ultrasonde detector](https://www.gotronic.fr/art-module-de-detection-us-hc-sr04-20912.htm)
  * 2 DC motors
  * 7-9V max 1A power supply
  
  
## Usage

1. Download [Git for Windows](https://gitforwindows.org/)
2. Clone the project : ``git clone https://github.com/simonhurault/aspirateur-robot.git``
3. Put the ``Motors`` folder into the librairies one in the arduino folder

How to use?

### The HC-SC04 captor

1. Link the Echo pin to the 4 digital pin of the arduino
2. Link the Trig pin to the 2 digital pin of the arduino
3. Supply the captor between 3.3 and 5V

### DC motors

1. Link + and - of the motors to the motor shield
2. Supply the motor shield between 7 and 9V

**Do not use the _3, 12, 9, 11, 13, 8, A0 and A1_ pin in the code. They are reserved to run the motor shield**


## License


This project is used under the [creative commons](https://creativecommons.org/licenses/by-nc-sa/2.5/deed.fr) license.

It was created by [Polytech Montpellier](https://www.polytech.umontpellier.fr/) students.
