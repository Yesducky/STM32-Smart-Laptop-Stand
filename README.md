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

|   Function  	|      Device/Config     	| Port 	| Pin 	|    	|    	|    	|    	|    	|    	|    	|    	|    	|    	|    	|
|:-----------:	|:----------------------:	|:----:	|:---:	|:--:	|:--:	|:--:	|:--:	|:--:	|:--:	|:--:	|:--:	|:--:	|:--:	|:--:	|
|    Camera   	|     Camera data bus    	|   B  	|  8  	|  9 	| 10 	| 11 	| 12 	| 13 	| 14 	| 15 	| 　 	| 　 	| 　 	| 　 	|
|             	|     Camera control     	|   C  	|  2  	|  3 	|  6 	|  7 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|             	|       Camera FIFO      	|   A  	|  2  	|  3 	|  8 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|             	|                        	|   C  	|  4  	|  5 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|             	|                        	|   D  	|  3  	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|     LCD     	|       LCD Display      	|   D  	|  0  	|  1 	|  4 	|  5 	|  7 	|  8 	|  9 	| 10 	| 11 	| 12 	| 14 	| 15 	|
|             	|                        	|   E  	|  1  	|  7 	|  8 	|  9 	| 10 	| 11 	| 12 	| 13 	| 14 	| 15 	| 　 	| 　 	|
|             	|        LCD Touch       	|   D  	|  13 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|             	|                        	|   E  	|  0  	|  2 	|  3 	|  4 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|     UART    	|         USART1         	|   A  	|  9  	| 10 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
| TIM1 (TRIG) 	|         HC-SR04        	|   A  	|  12 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
| TIM1 (ECHO) 	|         HC-SR04        	|   A  	|  11 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|   TIM3_CH1  	| Stepper Speed (Backup) 	|   A  	|  6  	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|   TIM3_CH2  	|      Stepper Speed     	|   A  	|  7  	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
| GPIO-OUTPUT 	|  Stepper Dir (Backup)  	|   E  	|  5  	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
| GPIO-OUTPUT 	|       Stepper Dir      	|   E  	|  6  	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
|   TIM4_CH1  	|           FAN          	|   B  	|  6  	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	| 　 	|
