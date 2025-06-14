/*
 * PinDefines.h
 *
 *  Created on: May 2, 2025
 *      Author: julian
 */

#ifndef INC_PINDEFINES_H_
#define INC_PINDEFINES_H_

/* Includes ------------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* PINS used as dig. inputs */

/* watering Buttons */
#define DIN1_BUTTON_WATERINGLVL_1 					(1 - 1) //PA12
#define DIN2_BUTTON_WATERINGLVL_2 					(2	- 1)//PA11
#define DIN3_BUTTON_CTRL_PUMP_1 					(3	- 1)//PB9
#define DIN10_FLOWMETER_DETECT 						(10	- 1)//PB13
/* motorCTRL Buttons */
#define DIN4_BUTTON_RETRACT_WATERINGARM_VERT_FULL 	(4	- 1)//PB2
#define DIN5_BUTTON_EXTEND_WATERINGARM_HORIZ 		(5	- 1)//PB1
#define DIN6_BUTTON_EXTEND_WATERINGARM_VERT 		(6	- 1)//PB15
#define DIN7_BUTTON_RETRACT_WATERINGARM_VERT 		(7	- 1)//PB14
#define DIN8_BUTTON_RETRACT_WATERINGARM_HORIZ 		(8	- 1)//PC6
#define DIN12_ENDSWITCH_1 							(12	- 1)//PC7
#define DIN13_ENDSWITCH_2      						(13	- 1)//PA9
/* fill watertank Buttons */
#define DIN9_BUTTON_PUMP2 							(9	- 1)//PC8 /* Button to activate water tank fill via pump2 */
#define DIN14_WATERLEVEL_SENS_1 					(14	- 1)//PA8
#define DIN15_WATERLEVEL_SENS_2 					(15	- 1)//PB10
/* EvalBoard User PushButton as Dummy */
#define DIN11_BUTTON_EVALUSER 						(11	- 1)//PC13


/* PINS used as dig. outputs */
#define DOUT1_PUMP1_VALVE //PC14 //PDOUT Ventil_1 Pumpe (Relais1) (direkt an Pumpe gekoppelt vor an; nach aus etc.; 0.5sek.)
#define DOUT2_PUMP1_WATER //PC2 //PDOUT Pumpe_1 Gießen (Relais3)
#define DOUT3_PUMP2_VALVE //PC15 //PDOUT Ventil_2 befüllen (Relais2) (fast immer offen, außer Füllstand == voll



/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/


#endif /* INC_PINDEFINES_H_ */
