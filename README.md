# STM32-Smart-Laptop-Stand

### Function:
Automatically adjust the height of the laptop stand according to the user's height. Manual adjustment also allowed.

#### Workflow: ####
1. User click the auto button on the touch screen
2. Camera capture an image and send to the computer
3. Use OpenCV to obtain the face position of the user 
4. Send the position data to STM32
5. Obtain the distance between the camera and user using ultrasonic distance sensor
6. Calculate the most suitable height for the user with these 2 data
7. Control the actuators to adjust the laptop stand to the most suitable height
8. Keep updating the current height on the screen during height adjustment

### Alt Function: ###
Laptop cooling fan - 3 different levels of fan speed can be adjusted through touch screen

### Hardware: ### 
- [x] STM32F103VET6   
- [X] Touch Screen   
- [X] 2x Actuator
- [X] 2x 28 Stepper motor 0.6A
- [X] 2x DM420 Stepper Driver
- [X] Fan
- [X] HC-SR04 Ultrasonic sensor
- [X] OV7725 Camera
- [X] 220 ohm resistor
- [X] 7-segments LED
- [X] 24V battery

<br>

###Pinout:###
<table class="tg">
<thead>
  <tr>
    <th class="tg-c3ow">Function</th>
    <th class="tg-c3ow">Device/Config</th>
    <th class="tg-c3ow">Port</th>
    <th class="tg-c3ow" colspan="12">Pin</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-c3ow">Camera</td>
    <td class="tg-c3ow">Camera data bus</td>
    <td class="tg-c3ow">B</td>
    <td class="tg-c3ow">8</td>
    <td class="tg-c3ow">9</td>
    <td class="tg-c3ow">10</td>
    <td class="tg-c3ow">11</td>
    <td class="tg-c3ow">12</td>
    <td class="tg-c3ow">13</td>
    <td class="tg-c3ow">14</td>
    <td class="tg-c3ow">15</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">Camera control</td>
    <td class="tg-c3ow">C</td>
    <td class="tg-c3ow">2</td>
    <td class="tg-c3ow">3</td>
    <td class="tg-c3ow">6</td>
    <td class="tg-c3ow">7</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">Camera FIFO</td>
    <td class="tg-c3ow">A</td>
    <td class="tg-c3ow">2</td>
    <td class="tg-c3ow">3</td>
    <td class="tg-c3ow">8</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">C</td>
    <td class="tg-c3ow">4</td>
    <td class="tg-c3ow">5</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">D</td>
    <td class="tg-c3ow">3</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">LCD</td>
    <td class="tg-c3ow">LCD Display</td>
    <td class="tg-c3ow">D</td>
    <td class="tg-c3ow">0</td>
    <td class="tg-c3ow">1</td>
    <td class="tg-c3ow">4</td>
    <td class="tg-c3ow">5</td>
    <td class="tg-c3ow">7</td>
    <td class="tg-c3ow">8</td>
    <td class="tg-c3ow">9</td>
    <td class="tg-c3ow">10</td>
    <td class="tg-c3ow">11</td>
    <td class="tg-c3ow">12</td>
    <td class="tg-c3ow">14</td>
    <td class="tg-c3ow">15</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">E</td>
    <td class="tg-c3ow">1</td>
    <td class="tg-c3ow">7</td>
    <td class="tg-c3ow">8</td>
    <td class="tg-c3ow">9</td>
    <td class="tg-c3ow">10</td>
    <td class="tg-c3ow">11</td>
    <td class="tg-c3ow">12</td>
    <td class="tg-c3ow">13</td>
    <td class="tg-c3ow">14</td>
    <td class="tg-c3ow">15</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">LCD Touch</td>
    <td class="tg-c3ow">D</td>
    <td class="tg-c3ow">13</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow"></td>
    <td class="tg-c3ow">E</td>
    <td class="tg-c3ow">0</td>
    <td class="tg-c3ow">2</td>
    <td class="tg-c3ow">3</td>
    <td class="tg-c3ow">4</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">UART</td>
    <td class="tg-c3ow">USART1</td>
    <td class="tg-c3ow">A</td>
    <td class="tg-c3ow">9</td>
    <td class="tg-c3ow">10</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">TIM1 (TRIG)</td>
    <td class="tg-c3ow">HC-SR04</td>
    <td class="tg-c3ow">A</td>
    <td class="tg-c3ow">12</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">TIM1 (ECHO)</td>
    <td class="tg-c3ow">HC-SR04</td>
    <td class="tg-c3ow">A</td>
    <td class="tg-c3ow">11</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">TIM3_CH1</td>
    <td class="tg-c3ow">Stepper Speed (Backup)</td>
    <td class="tg-c3ow">A</td>
    <td class="tg-c3ow">6</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">TIM3_CH2</td>
    <td class="tg-c3ow">Stepper Speed</td>
    <td class="tg-c3ow">A</td>
    <td class="tg-c3ow">7</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">GPIO-OUTPUT</td>
    <td class="tg-c3ow">Stepper Dir (Backup)</td>
    <td class="tg-c3ow">E</td>
    <td class="tg-c3ow">5</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">GPIO-OUTPUT</td>
    <td class="tg-c3ow">Stepper Dir</td>
    <td class="tg-c3ow">E</td>
    <td class="tg-c3ow">6</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
  <tr>
    <td class="tg-c3ow">TIM4_CH1</td>
    <td class="tg-c3ow">FAN</td>
    <td class="tg-c3ow">B</td>
    <td class="tg-c3ow">6</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
    <td class="tg-c3ow">　</td>
  </tr>
</tbody>
</table>

### Design: ###

<img src="https://github.com/Yesducky/STM32-Smart-Laptop-Stand/blob/main/assets/img4.jpg" alt="Design Front">
<img src="https://github.com/Yesducky/STM32-Smart-Laptop-Stand/blob/main/assets/img5.jpg" width="1000px;" alt="Design Side">

### Outcome: ###
<img src="https://github.com/Yesducky/STM32-Smart-Laptop-Stand/blob/main/assets/img1.jpg" alt="With Laptop">
<img src="https://github.com/Yesducky/STM32-Smart-Laptop-Stand/blob/main/assets/img2.jpg" alt="Without Laptop">
<img src="https://github.com/Yesducky/STM32-Smart-Laptop-Stand/blob/main/assets/img3.jpg" alt="All components">


