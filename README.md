# arduino_projects

shortcuts:

[Link Text](#robot_car_1)

### robot_car_1
This is an Arduino code that **controls a car** powered by an Arduino board. The car is equipped with a **servo motor** for steering and an **ultrasonic sensor** for obstacle detection. The car can receive commands from a **Bluetooth module** to *move forward, backward, turn left, turn right and stop.*

The `Servo.h` library is used to **control the servo motor**, while the `Ultrasonic.h` library is used to **measure the distance** between the ultrasonic sensor and an object in front of it. The **car is driven by** a `L298N motor driver`, which is connected to the Arduino board through the defined digital pins.

The main loop function listens to the Bluetooth connection signals and performs the necessary action based on the received signal. The program first checks the received signal and then performs the corresponding action by calling a respective function. For example, `if the received signal is '1'`, the servo motor moves forward and the ultrasonic sensor measures the distance to the obstacle. `If the distance is not 0 and greater than 20`, the car moves forward.

The car is programmed to move `forward`, `backward`, `turn left`, `turn right`, and `stop`. The car also stops if an obstacle is detected within 20 cm of its path. The program continuously listens to the Bluetooth connection and performs the necessary action until the car is stopped by receiving the signal '5'.

