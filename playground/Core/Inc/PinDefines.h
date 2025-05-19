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
#define DIN9_BUTTON_PUMP2 //PC8 /* Button to activate water tank fill via pump2 */
#define DIN8_BUTTON_RETRACT_WATERINGARM_HORIZ //PC6
#define DIN1_BUTTON_WATERINGLVL_1 	0	//PA12
#define DIN2_BUTTON_WATERINGLVL_2 	1	//PA11
#define DIN3_BUTTON_CTRL_PUMP_1 	2	//PB12
#define DIN4_BUTTON_RETRACT_WATERINGARM_VERT_FULL //PB2
#define DIN5_BUTTON_EXTEND_WATERINGARM_HORIZ //PB1
#define DIN6_BUTTON_EXTEND_WATERINGARM_VERT //PB15
#define DIN7_BUTTON_RETRACT_WATERINGARM_VERT //PB14
#define DIN10_FLOWMETER_DETECT //PB13
#define DIN11_BUTTON_EVALUSER 12//PC13
//PC7 	Y		DIN Endschalter1
//PA9 	Y	    DIN Endschalter2
//PA8		Y	    DIN Füllstandsensor1
//PB10	Y		DIN Füllstandsensor2


/* PINS used as dig. outputs */
#define DOUT1_PUMP1_VALVE //PC14 //PDOUT Ventil_1 Pumpe (Relais1) (direkt an Pumpe gekoppelt vor an; nach aus etc.; 0.5sek.)
#define DOUT2_PUMP1_WATER //PC2 //PDOUT Pumpe_1 Gießen (Relais3)
#define DOUT3_PUMP2_VALVE //PC15 //PDOUT Ventil_2 befüllen (Relais2) (fast immer offen, außer Füllstand == voll



/* External variables --------------------------------------------------------*/
/* Function declarations -----------------------------------------------------*/


#endif /* INC_PINDEFINES_H_ */
