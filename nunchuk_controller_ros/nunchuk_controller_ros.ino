#include <Wire.h>
#include <Nunchuk.h>
#include <ESP8266WiFi.h>

#include <ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>

#define ROSSERIAL_ARDUINO_TCP

#include "Parameters.h"

double lin = 0;
double ang = 0;

//here goes the address of your ros master
IPAddress server(192, 168, 1, 2);
const uint16_t serverPort = 11411;

const int sclPin = D1;
const int sdaPin = D2;

ros::NodeHandle nh;
geometry_msgs::Twist msg;
ros::Publisher cmd_pub("cmd_vel", &msg);

void setup() {
    Wire.begin(sdaPin, sclPin);

    WiFi.begin(WIFI_SSID, WIFI_PWD);
    while (WiFi.status() != WL_CONNECTED)
    {
      delay(500);
    }
    nh.getHardware()->setConnection(server, serverPort);
    
    nh.initNode();
    nh.advertise(cmd_pub);

    nunchuk_init();
    
}
void loop() {
    nunchuk_read();

    #ifdef UNRELIABLE 
    if(nunchuk_buttonZ() == 0){
      lin = mapf(nunchuk_roll(), MIN_ROLL, MAX_ROLL, MIN_LIN, MAX_LIN);
      ang = mapf(nunchuk_pitch(), MIN_PITCH, MAX_PITCH, MIN_ANG, MAX_ANG);
    } else{
      lin = 0;
      ang = 0;
    }
    #endif
    
    #ifdef RELIABLE
     if(nunchuk_buttonZ() == 0){
      lin = mapf(nunchuk_joystickY(), MIN_JOY_Y, MAX_JOY_Y, MIN_LIN, MAX_LIN);
      ang = mapf(nunchuk_joystickX(), MIN_JOY_X, MAX_JOY_X, MIN_ANG, MAX_ANG);
    } else{
      lin = 0;
      ang = 0;
    }
    #endif
    
    msg.linear.x = lin;
    msg.angular.z = ang;
   
    cmd_pub.publish(&msg);
    nh.spinOnce();
    delay(10);
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
