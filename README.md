# STM32-Smart-Laptop-Stand
Hardware:  
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

<style type="text/css">
.tg  {border-collapse:collapse;border-spacing:0;}
.tg td{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  overflow:hidden;padding:10px 5px;word-break:normal;}
.tg th{border-color:black;border-style:solid;border-width:1px;font-family:Arial, sans-serif;font-size:14px;
  font-weight:normal;overflow:hidden;padding:10px 5px;word-break:normal;}
.tg .tg-c3ow{border-color:inherit;text-align:center;vertical-align:top}
</style>
<table class="tg">
<thead>
  <tr>
    <th class="tg-c3ow">Function</th>
    <th class="tg-c3ow">Device/Config</th>
    <th class="tg-c3ow">Port</th>
    <th class="tg-c3ow">Pin</th>
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
