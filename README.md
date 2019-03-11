# Simple Alarm Clock

[![image](https://github.com/lhiep/alarm-clock/blob/master/IMG_2947.jpg)](https://www.youtube.com/watch?v=hrCGJ-lAgcM)

[TO WATCH THE DEMO VIDEO, CLICK HERE!](https://www.youtube.com/watch?v=hrCGJ-lAgcM)

In this project, I exploered the feasibility of using an Arduino Uno to construct a basic alarm clock. As seen above, no time module is needed. Instead, the millis() function of the Arduino is used to keep time. The millis() function keeps track of how many seconds have ellapsed since the Arduino started running for up to 50 days before resetting back to zero. We can then easily extract the hour and minute from this, adding an offset that the user can input, and display back out a somewhat accurate clock. By adding buttons, an LED, and a piezzo speaker, this is turned into a functional alarm clock.

To use the code, refer to the chart below for wiring.

![chart](https://github.com/lhiep/alarm-clock/blob/master/Capture.JPG?raw=true)
