
# NaviGuard: Robot Service Car

NaviGuard is a Robot service car designed to assist people with disabilities. This Arduino-based vehicle is equipped with the primary feature of obstacle avoidance. 

## Inspiration

I was inspired by the ultrasonic sensor which resembled a pair of robot eyes, like the WALL-E robot. This spark was reared by learning more about building a robot.  

![23298-8-wall-e](https://git.arts.ac.uk/storage/user/627/files/1412a2e8-637f-45d1-9cee-adcdab8984ce)


## Research

### **Input: Ultrasonic Sensor**

I knew that I would need an ultrasonic sensor acting as an input to the Arduino, providing it with distance readings that are used to detect obstacles. 

### **Output: DC Motors**

The DC motors would be the output for the Arduino, driving the wheel to move the robot car when an obstacle is detected.

### Components Required

My research began with looking at youtube videos to see how the assembly of the project would come together.  I’ve added all the videos I watched and referred to a playlist. 

Playlist link: https://www.youtube.com/playlist?list=PLtMDXo_irXPKXK46QgWfbt3W2foczgXFl

# Process

### Tinkercad Sketch

To begin with I simulated a basic version of my robot in Tinkercad. Since the application didn’t have a motor shield component but an L293D motor driver to drive two wheels I swapped the shield with two L293D motor drivers instead. 

![NaviGuard_ Robot Service Car ](https://git.arts.ac.uk/storage/user/627/files/95cffa1a-2279-4535-99d9-2b8d7a2a3824)


I then wrote a simple code to run two motors using digitalWrite and setting the motors’ values to HIGH and LOW. I also tested the ultrasonic sensor using newPing library and the servo using sweep. 

### 3D Printing

Following this, I proceeded with my 3D printing of a Chassis for my Robot Car. I had no experience with 3D modeling software and given the nature of the print I needed, I decided to download a model from ThingyVerse. 
<img width="925" alt="Screenshot 2023-06-08 at 2 29 05 PM" src="https://git.arts.ac.uk/storage/user/627/files/59e56663-09f5-4736-be45-35cd3faed490">
<img width="776" alt="Screenshot 2023-06-08 at 5 48 48 PM" src="https://git.arts.ac.uk/storage/user/627/files/1dfcaa15-8c5b-464b-b1b4-dfa9a8f00f7d">


The final 3D printed chassis. 

Robot Car Print files:

[Chassis Top.stl](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/644e16b9-3c12-4800-a2d5-a86e871d19f9/Chassis_Top.stl)

[Chassis.stl](https://s3-us-west-2.amazonaws.com/secure.notion-static.com/b658586e-0d92-43a5-a518-48e0599d951e/Chassis.stl)

[]()

Thingyverse options considered: 

https://www.thingiverse.com/thing:5037734

https://www.thingiverse.com/thing:4152818

### Components Required

Based on my research my initial plan was to build a four-wheel robot with a L293D motor driver. However, I learned that we had access to only an L298N motor driver which could drive only two wheels. So, I bought an L293D motor driver shield from Amazon.  (https://www.amazon.co.uk/dp/B073GRYT5R?psc=1&ref=ppx_yo2ov_dt_b_product_details)

I also found that there were no wheels available so I ordered a kit of 4 gear motors and 4 toy wheels too from Amazon. (https://www.amazon.co.uk/dp/B08D39MFN1?psc=1&ref=ppx_yo2ov_dt_b_product_details)

Here are the components used initially: (L293D Motor Driver Version) 

- Arduino Leonardo
- Ultrasonic Sensor
- L293D Motor Shield
- 4 Gear Motors
- 9V Battery
- A Set of 4 motors and wheels
- Servo Motor
- 3  M3 * 16mm Socket Head Screws

## Building Version 1: NaviGuard 1.0

To make writing and scaling the motor code easier, I found that there was a library called the Adafruit Motor Shield Library which helps control the direction and speed of the motors efficiently. I expanded my knowledge of this library by referring to its official documentation on its website as well as a few other links I found on Google. 

- https://cdn-learn.adafruit.com/downloads/pdf/afmotor-library-reference.pdf
- https://5.imimg.com/data5/PX/UK/MY-1833510/l293d-based-arduino-motor-shield.pdf
- https://www.engineersgarage.com/arduino-l293d-motor-driver-shield-tutorial/
- https://playground.arduino.cc/Main/AdafruitMotorShield/

![Image](https://git.arts.ac.uk/storage/user/627/files/1ec44a26-af2c-48e5-b7ee-2c07d9b55d56)


I then took the existing code (L298N) version to run 2 motors and added AF Motor library functionalities to run 4 motors. [full code uploaded under “V1.0_L293DmotorShield.ino”]


### Soldering

Subsequently, I soldered the VCC pin on the ultrasonic sensor to +5v and the GND pin on the ultrasonic sensor to GND on the L293D motor shield. The trig and echo pins had also been soldered to digital pins 2 and 13 respectively on the L293D motor shield.

(pins 2 and 13 were used as they were the only two free pins not being used by the Arduino) 

A pair of wires have also been soldered to each gear motor which is connected to each DC motor connection (M1, M2, M3, M4) on the motor driver

I also stuck down the motors and the 9V battery to the chassis and connected the servo and the ultrasonic sensor. 


![IMG_8945](https://git.arts.ac.uk/storage/user/627/files/07280c0b-deb9-4641-aa17-3255a4e9fa42)
<img width="907" alt="Screenshot 2023-06-08 at 5 58 34 PM" src="https://git.arts.ac.uk/storage/user/627/files/7ff83a41-3aee-4c28-954a-d745eb128b95">

## Debugging

With everything setup, I ran the code but I got a very troubling error saying "This chip is not supported!” 

I tried debugging it by deleting duplicate libraries, moving the existing AF Motor Library to the right folder and downloading a 3rd Party Source party library (supported by all Arduinos) after finding that the *AF_DCMotor library is not compatible with the Arduino Leonardo*

*Source: https://github.com/adafruit/Adafruit-Motor-Shield-library*

*Ref: https://forum.arduino.cc/t/makershed-motorshield_v1-w-arduino-leonardo/613695*

*Another source (I didn’t try downloading the library from here): https://resources.oreilly.com/examples/0636920028024/-/tree/master/libraries*

I even attended two technical tutorials with Matt trying to solve the problem during which we tested the model and code with the following changes:

- Arduino Diecimila (couldn’t find an Uno)
- Installing an older version of the Arduino IDE (1.8.19) as it allows us to select the processor which isn't possible in the latest version of the IDE.
- Switch out the continuous servo motor and use an SG90 version instead (I hot glued it, so removed it and used a discontinuous one instead).

However, the motors didn’t run after all these changes. Only the servo and ultrasonic sensor worked. We narrowed down the problem to 

1. Arduino (Uno would’ve been the best option)
2. The library and its compatibility with the Arduino
3. The motor driver (I didn’t buy it from the official website, on which it is much more expensive)

<img width="839" alt="Screenshot 2023-06-08 at 11 46 34 PM" src="https://git.arts.ac.uk/storage/user/627/files/190ec2cb-0c97-47a1-8f50-d189bd9949ab">
<img width="738" alt="Screenshot 2023-06-08 at 11 46 05 PM" src="https://git.arts.ac.uk/storage/user/627/files/4b6e9c04-24aa-4b49-b410-9d48f48f42e3">

## Building Version 2: NaviGuard 2.0

This left me with only one option to start over with two L298N motor drivers to each run two motors. So, I repeated the process of unassembling and removing soldering. 

### Re-build & Final Outcome

I started off by going back to the simple L298N motor driver code to run 2 motors. I added an additional mini breadboard to create all the GND and Voltage connections. With this, I tested running the back two wheels which worked successfully. 

I then doubled and modified the code to include the front two wheels which I also connected to another L298N motor driver. All 4 motors worked on testing to my relief. 

<img width="988" alt="Screenshot 2023-06-08 at 11 49 44 PM" src="https://git.arts.ac.uk/storage/user/627/files/d4ca9fb3-59e7-474f-8fd0-6b639b5d2a3f">

I then wrote the code for the ultrasonic sensor, servo and the conditions to turn the motors in response to the distance sensed by the sensor. 

Finally, combining all the parts after testing them individually the robot car worked all together. 

Furthermore, I made connections to have the Arduino power itself (5V) using the Vin pin and a second GND pin along with an external 9V power source to run the motors. 

In order to have the car run by itself without using a cable attached to it, I wanted to power it using a 9v battery (which was glued onto the chassis) after initiating a few test runs. However, when I tried running it with the attached battery only two wheels moved often at very different slow speeds. Presuming enough power wasn’t being supplied to the wheels I used a multimeter to check the voltage and it revealed to be 7V. 

## Conclusion

NaviGuard is a Robot Service Car designed to assist people with disabilities by providing obstacle-avoidance capabilities. Throughout the project, I gained inspiration from the WALL-E robot and conducted thorough research on the required components and functionality.

The development process involved simulating the robot in Tinkercad, 3D printing the chassis, and assembling the necessary components. Initially, I planned to use the L293D motor driver for four wheels, but due to limitations, I switched to the L298N motor driver to control two wheels.

I faced challenges with library compatibility and motor functionality, leading to a rebuild using two L298N motor drivers. Soldering, code modifications, and extensive testing resulted in a successfully functioning robot car.

Looking ahead, I plan to enhance the project by integrating Bluetooth voice control, allowing users to operate the car remotely. This future scope will further improve the accessibility and usability of NaviGuard for individuals with disabilities.

Overall, NaviGuard represents an initial step towards developing a versatile and user-friendly robot service car for individuals with specific mobility needs.

## References

L293D Motor Driver

- https://www.ti.com/lit/ds/symlink/l293d.pdf?ts=1685366116587&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FL293D
- https://components101.com/modules/l293n-motor-driver-module
- https://5.imimg.com/data5/PX/UK/MY-1833510/l293d-based-arduino-motor-shield.pdf
- https://www.engineersgarage.com/arduino-l293d-motor-driver-shield-tutorial/

AF Motor Library

- https://cdn-learn.adafruit.com/downloads/pdf/afmotor-library-reference.pdf
- https://playground.arduino.cc/Main/AdafruitMotorShield/

Downloading Library

- https://www.instructables.com/Arduino-Install-and-Use-Arduino-Libraries/
- https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries

Servo Motor Datasheet SG90

- https://datasheetspdf.com/pdf-file/791970/TowerPro/SG90/1

Error debug

- https://forum.arduino.cc/t/error-message-i-dont-understand/90146

H-bridge

- http://icrobotics.co.uk/wiki/index.php/H_Bridge
- https://www.arduino.cc/documents/datasheets/H-bridge_motor_driver.PDF
- https://www.instructables.com/Arduino-L293D-Motor-Driver-Shield-Tutorial/

Distance calculation (in code reference) 

- https://www.instructables.com/Controlling-a-Servo-With-an-Ultrasonic-Sensor-Usin/
