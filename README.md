# Nunchuk ROS controller
Drive your robot with an unreliable controller!
Have you always wanted to drive your robot with a nunchuk? Now you can!

## Disclaimer
Accelerometers aren't meant to be used this way, the control is very unreliable.
Please use this sketch at your own risk, preferably on cheap robots you don't mind getting hurt in the process.

### Hardware
Microcontroller: Wemos D1

Nunchuk (duh)

Pinout:

| Wemos | Nunchuk |
|-------|---------|
| 3.3V  | +       |
| GND   | -       |
| D1    | C       |
| D2    | D       |

## Extra libraries
[Library for nunchuk readings](https://github.com/infusion/Fritzing/blob/master/Nunchuk/Nunchuk.h)

For the ROS libraries follow the guide on [ROS wiki](http://wiki.ros.org/rosserial_arduino/Tutorials/Arduino%20IDE%20Setup)

## Setup
Define your wifi ssid and wifi password in the "Parameters.h" file.
Change the ROS Master address in the main file.

## Usage
Launch ROS
``` 
roscore 
```
Launch rosserial node
``` 
rosrun rosserial_python serial_node.py tcp
```

The linear velocity is the roll angle, the angular velocity is the pitch angle.
You can brake using the Z button.

If you really want to use this thing for real you can change the mode to RELIABLE in the "Parameters.h" file, so the values are read from the joystick and not from the accelerometers. 

You can also modify the min/max angular and linear velocity, just change the values in the "Parameters.h" file

Have fun!

