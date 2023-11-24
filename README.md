# STM32-Smart-Laptop-Stand
Hardware:  
- [x] STM32F103VET6   
- [X] Ultrasonic sensor   
- [X] 2x Actuator
- [X] 2x 28 Stepper motor 0.6A
- [X] 2x DM420 Stepper Driver
- [X] HMC5883L Digital Compass
- [X] Fan
- [X] Temperature sensor

| Pin 	| Function    	| Usage                  	|
|-----	|-------------	|------------------------	|
| A6  	| TIM3_CH1    	| Stepper Speed (Backup) 	|
| A7  	| TIM3_CH2    	| Stepper Speed          	|
| E5  	| GPIO-OUTPUT 	| Stepper Dir (Backup)   	|
| E6  	| GPIO-OUTPUT 	| Stepper Dir            	|
| B10 	| I2C2        	| HMC5883L               	|
| B11 	| I2C2        	| HMC5883L               	|
| B6  	| TIM4_CH1    	| FAN                    	|
|     	|             	|                        	|
|     	|             	|                        	|
|     	|             	|                        	|
|     	|             	|                        	|
|     	|             	|                        	|
|     	|             	|                        	|
|     	|             	|                        	|
