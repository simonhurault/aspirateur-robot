#Motors
==========

This is a library for controling 2 DC motors for robot.

```cpp
motors.move(1,105); //make the motors go forward at 105 speed
motors.stop();      //stop the motors
motors.turn(255);   //make the robot turn by making the right wheel go frontward and the left wheel go backward at 255 speed
```

##Table of Contents
-----------------

  * [Requirements](#requirements)
  * [Usage](#usage)
  * [License](#license)


##Requirements
------------

Motors requires the following to run:

  * [Arduino](https://www.arduino.cc/)
  * [2 DC motors] 
  * [7-9V max 1A power supply ]
  
  
##Usage
-----

-Put the Motors folder on the librairies one into the arduino folder.
-Then use :

```cpp
#include <Motors.h>
```
to add the library to your code.


The `motors` object has the following methods.

### `motors.move( int, int)`

Make the 2 DC motors go in the same direction to allow the robot go gorward or backward.

`int` is the direction. 0 is backward another number is forward.
`int` is the speed. It must be between 0 and 255.
`return` is void.

```cpp
//Example
motors.move(1, 105); // make the DC motors go forward at 105 speed
motors.move(0, 255); // make the DC motors go backward at 255 speed
```

### `motors.turn(int)`

Make the A motor go forward and the B one backward.

`int` is the speed. It must be between 0 and 255.
`return` is void.

```cpp
//Example
motors.turn(90);
```

### `motors.stop()`

Stop the 2 motors.

```cpp
//Example
motors.stop();
```

##License
-------

Motors is used under the [creative commons] (https://creativecommons.org/licenses/by-nc-sa/2.5/deed.fr) license.
This library was created by Simon Hurault.



