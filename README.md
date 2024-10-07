This project simulates a traffic light system for two roads using an Arduino Nano, LEDs, and a 7-segment display. The system controls the flow of traffic by alternating between red and green lights based on road congestion, which is detected through push buttons. The 7-segment display shows a countdown timer during transitions, enhancing the realism of the traffic light system.

Components :

1. Arduino Nano : Microcontroller responsible for controlling the traffic light logic and timing.
2. Breadboard: Platform for assembling the electronic circuit without the need for soldering.
3. LEDs: Four LEDs represent the traffic lights: red and yellow for Road 1, yellow and green for Road 2.
4. Resistors: Used to limit current flowing through the LEDs, preventing damage.
5. Jumper wires: Connect the components on the breadboard to the Arduino board.
6. Push buttons: Used to simulate congestion on each road, allowing manual control of traffic light changes.
7. A 7-segment display: Displays a countdown timer during transitions between red, yellow, and green lights.

Circuit Design :

The LEDs and buttons are connected to the Arduino's analog pins. Resistors are placed in series with the LEDs to limit the current. Each road has its own buttons to simulate traffic congestion.

Road 1: Connected to red and yellow LEDs.
Road 2: Connected to yellow and green LEDs.
Buttons: Each road has a push button that indicates whether the road is busy or not.
The 7-segment display is used to show a countdown during light transitions, improving the user experience by visually indicating the remaining time for each signal.

Traffic Light Logic :

The traffic light system follows this simplified control logic:

Button Press Detection: When the button for Road 1 is pressed, traffic lights for Road 1 turn red, and Road 2 gets the green light, allowing traffic to pass. When the button for Road 2 is pressed, the reverse happens, and Road 1 gets the green light.
Transition Time: A countdown timer is displayed during transitions (red-to-green or green-to-yellow), signaling the change in light.
Countdown: The 7-segment display shows the time remaining for each transition. This gives an indication of when the light will change.
Main Logic Flow:
If Road 1 is busy (button pressed), the red light for Road 1 is activated, and the green light for Road 2 is turned on.
If Road 2 is busy, the green light for Road 1 turns on, while the red light for Road 2 is activated.
The yellow light is shown as a warning before switching between green and red lights on both roads.

Conclusion :

This traffic light system is a simplified model that mimics the real-world traffic control mechanism. The system successfully manages traffic on two roads based on button input, allowing users to simulate congestion and observe the traffic light cycle. The use of an Arduino and simple electronic components such as LEDs, resistors, and a 7-segment display makes this project an excellent introduction to traffic light control systems.

