/*
 *      Module: Port
 *      File name : Port_Cfg.h
 *      Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *      Created on: 6 Feb 2024
 *      Author: Abdallah Elgendy
 */

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_OFF)


/* Pre-compile option for presence of PortSetPinDirection API */
#define PORT_SET_PIN_DIRECTION_API            (STD_ON)

/* Pre-compile option for presence of PortSetPinMode API */
#define PORT_SET_PIN_MODE_API                 (STD_ON)

/* Number of the configured PINS */
#define PORT_CONFIGURED_PINS              (43U)

#define UNLOCK_VALUE                    0x4C4F434B

/************************ Pin modes **********************************/
  #define PORT_DIO_MODE                     (0U)
  #define PORT_ALTER_FUNC_UART_MODE         (1U)
  #define PORT_ALTER_FUNC_SSI_MODE          (2U)
  #define PORT_ALTER_FUNC_TWI_MODE          (3U)
  #define PORT_ALTER_FUNC_PWM_MODE          (4U)
  #define PORT_ALTER_FUNC_CAN_MODE          (5U)
  #define PORT_ALTER_FUNC_USB_MODE          (6U)
  #define PORT_ALTER_FUNC_WDT_MODE          (7U)
  #define PORT_ALTER_FUNC_NMI_MODE          (8U)
  #define PORT_ALTER_FUNC_GPT_MODE          (9U)
  #define PORT_ALTER_FUNC_ADC_MODE          (10U)





/************************ Ports symbol names **********************************/

#define PORT_A                            (0U)
#define PORT_B                            (1U)
#define PORT_C                            (2U)
#define PORT_D                            (3U)
#define PORT_E                            (4U)
#define PORT_F                            (5U)


/************************ Pins symbol names **********************************/

#define PORT_P0                            (0U)
#define PORT_P1                            (1U)
#define PORT_P2                            (2U)
#define PORT_P3                            (3U)
#define PORT_P4                            (4U)
#define PORT_P5                            (5U)
#define PORT_P6                            (6U)
#define PORT_P7                            (7U)



/************************ Port A pin symbol names **********************************/
#define PORTA_PA0               (0U)
#define PORTA_PA1               (1U)
#define PORTA_PA2               (2U)
#define PORTA_PA3               (3U)
#define PORTA_PA4               (4U)
#define PORTA_PA5               (5U)
#define PORTA_PA6               (6U)
#define PORTA_PA7               (7U)



/************************ Port B pin symbol names **********************************/

#define PORTB_PB0               (8U)
#define PORTB_PB1               (9U)
#define PORTB_PB2               (10U)
#define PORTB_PB3               (11U)
#define PORTB_PB4               (12U)
#define PORTB_PB5               (13U)
#define PORTB_PB6               (14U)
#define PORTB_PB7               (15U)



/************************ Port C pin symbol names **********************************/

#define PORTC_PC0               (16U)
#define PORTC_PC1               (17U)
#define PORTC_PC2               (18U)
#define PORTC_PC3               (19U)
#define PORTC_PC4               (20U)
#define PORTC_PC5               (21U)
#define PORTC_PC6               (22U)
#define PORTC_PC7               (23U)


/************************ Port D pin symbol names **********************************/

#define PORTD_PD0               (24U)
#define PORTD_PD1               (25U)
#define PORTD_PD2               (26U)
#define PORTD_PD3               (27U)
#define PORTD_PD4               (28U)
#define PORTD_PD5               (29U)
#define PORTD_PD6               (30U)
#define PORTD_PD7               (31U)

/************************ Port E pin symbol names **********************************/


#define PORTE_PE0               (32U)
#define PORTE_PE1               (33U)
#define PORTE_PE2               (34U)
#define PORTE_PE3               (35U)
#define PORTE_PE4               (36U)
#define PORTE_PE5               (37U)


/************************ Port F pin symbol names **********************************/

#define PORTF_PF0               (38U)
#define PORTF_PF1               (49U)
#define PORTF_PF2               (40U)
#define PORTF_PF3               (41U)
#define PORTF_PF4               (42U)




/****************************** PORT A PIN 0 ****************************************************/

#define PORTA_P0_DIRECTION          PORT_PIN_IN
#define PORTA_P0_MODE               PORT_DIO_MODE
#define PORTA_P0_RESISTOR           OFF
#define PORTA_P0_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P0_DIR_CHANGE         STD_OFF
#define PORTA_P0_MODE_CHANGE        STD_OFF

/****************************** PORT A PIN 1 ****************************************************/

#define PORTA_P1_DIRECTION          PORT_PIN_IN
#define PORTA_P1_MODE               PORT_DIO_MODE
#define PORTA_P1_RESISTOR           OFF
#define PORTA_P1_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P1_DIR_CHANGE         STD_OFF
#define PORTA_P1_MODE_CHANGE        STD_OFF

/****************************** PORT A PIN 2 ****************************************************/

#define PORTA_P2_DIRECTION          PORT_PIN_IN
#define PORTA_P2_MODE               PORT_DIO_MODE
#define PORTA_P2_RESISTOR           OFF
#define PORTA_P2_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P2_DIR_CHANGE         STD_OFF
#define PORTA_P2_MODE_CHANGE        STD_OFF

/****************************** PORT A PIN 3 ****************************************************/

#define PORTA_P3_DIRECTION          PORT_PIN_IN
#define PORTA_P3_MODE               PORT_DIO_MODE
#define PORTA_P3_RESISTOR           OFF
#define PORTA_P3_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P3_DIR_CHANGE         STD_OFF
#define PORTA_P3_MODE_CHANGE        STD_OFF


/****************************** PORT A PIN 4 ****************************************************/

#define PORTA_P4_DIRECTION          PORT_PIN_IN
#define PORTA_P4_MODE               PORT_DIO_MODE
#define PORTA_P4_RESISTOR           OFF
#define PORTA_P4_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P4_DIR_CHANGE         STD_OFF
#define PORTA_P4_MODE_CHANGE        STD_OFF


/****************************** PORT A PIN 5 ****************************************************/

#define PORTA_P5_DIRECTION          PORT_PIN_IN
#define PORTA_P5_MODE               PORT_DIO_MODE
#define PORTA_P5_RESISTOR           OFF
#define PORTA_P5_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P5_DIR_CHANGE         STD_OFF
#define PORTA_P5_MODE_CHANGE        STD_OFF



/****************************** PORT A PIN 6 ****************************************************/

#define PORTA_P6_DIRECTION          PORT_PIN_IN
#define PORTA_P6_MODE               PORT_DIO_MODE
#define PORTA_P6_RESISTOR           OFF
#define PORTA_P6_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P6_DIR_CHANGE         STD_OFF
#define PORTA_P6_MODE_CHANGE        STD_OFF


/****************************** PORT A PIN 7 ****************************************************/

#define PORTA_P7_DIRECTION          PORT_PIN_IN
#define PORTA_P7_MODE               PORT_DIO_MODE
#define PORTA_P7_RESISTOR           OFF
#define PORTA_P7_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTA_P7_DIR_CHANGE         STD_OFF
#define PORTA_P7_MODE_CHANGE        STD_OFF




/****************************** PORT B PIN 0 ****************************************************/

#define PORTB_P0_DIRECTION          PORT_PIN_IN
#define PORTB_P0_MODE               PORT_DIO_MODE
#define PORTB_P0_RESISTOR           OFF
#define PORTB_P0_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P0_DIR_CHANGE         STD_OFF
#define PORTB_P0_MODE_CHANGE        STD_OFF

/****************************** PORT B PIN 1 ****************************************************/

#define PORTB_P1_DIRECTION          PORT_PIN_IN
#define PORTB_P1_MODE               PORT_DIO_MODE
#define PORTB_P1_RESISTOR           OFF
#define PORTB_P1_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P1_DIR_CHANGE         STD_OFF
#define PORTB_P1_MODE_CHANGE        STD_OFF

/****************************** PORT B PIN 2 ****************************************************/

#define PORTB_P2_DIRECTION          PORT_PIN_IN
#define PORTB_P2_MODE               PORT_DIO_MODE
#define PORTB_P2_RESISTOR           OFF
#define PORTB_P2_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P2_DIR_CHANGE         STD_OFF
#define PORTB_P2_MODE_CHANGE        STD_OFF

/****************************** PORT B PIN 3 ****************************************************/

#define PORTB_P3_DIRECTION          PORT_PIN_IN
#define PORTB_P3_MODE               PORT_DIO_MODE
#define PORTB_P3_RESISTOR           OFF
#define PORTB_P3_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P3_DIR_CHANGE         STD_OFF
#define PORTB_P3_MODE_CHANGE        STD_OFF


/****************************** PORT B PIN 4 ****************************************************/

#define PORTB_P4_DIRECTION          PORT_PIN_IN
#define PORTB_P4_MODE               PORT_DIO_MODE
#define PORTB_P4_RESISTOR           OFF
#define PORTB_P4_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P4_DIR_CHANGE         STD_OFF
#define PORTB_P4_MODE_CHANGE        STD_OFF


/****************************** PORT B PIN 5 ****************************************************/

#define PORTB_P5_DIRECTION          PORT_PIN_IN
#define PORTB_P5_MODE               PORT_DIO_MODE
#define PORTB_P5_RESISTOR           OFF
#define PORTB_P5_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P5_DIR_CHANGE         STD_OFF
#define PORTB_P5_MODE_CHANGE        STD_OFF



/****************************** PORT B PIN 6 ****************************************************/

#define PORTB_P6_DIRECTION          PORT_PIN_IN
#define PORTB_P6_MODE               PORT_DIO_MODE
#define PORTB_P6_RESISTOR           OFF
#define PORTB_P6_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P6_DIR_CHANGE         STD_OFF
#define PORTB_P6_MODE_CHANGE        STD_OFF


/****************************** PORT B PIN 7 ****************************************************/

#define PORTB_P7_DIRECTION          PORT_PIN_IN
#define PORTB_P7_MODE               PORT_DIO_MODE
#define PORTB_P7_RESISTOR           OFF
#define PORTB_P7_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTB_P7_DIR_CHANGE         STD_OFF
#define PORTB_P7_MODE_CHANGE        STD_OFF





/****************************** PORT C PIN 0 ****************************************************/

#define PORTC_P0_DIRECTION          PORT_PIN_IN
#define PORTC_P0_MODE               PORT_DIO_MODE
#define PORTC_P0_RESISTOR           OFF
#define PORTC_P0_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P0_DIR_CHANGE         STD_OFF
#define PORTC_P0_MODE_CHANGE        STD_OFF

/****************************** PORT C PIN 1 ****************************************************/

#define PORTC_P1_DIRECTION          PORT_PIN_IN
#define PORTC_P1_MODE               PORT_DIO_MODE
#define PORTC_P1_RESISTOR           OFF
#define PORTC_P1_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P1_DIR_CHANGE         STD_OFF
#define PORTC_P1_MODE_CHANGE        STD_OFF

/****************************** PORT C PIN 2 ****************************************************/

#define PORTC_P2_DIRECTION          PORT_PIN_IN
#define PORTC_P2_MODE               PORT_DIO_MODE
#define PORTC_P2_RESISTOR           OFF
#define PORTC_P2_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P2_DIR_CHANGE         STD_OFF
#define PORTC_P2_MODE_CHANGE        STD_OFF

/****************************** PORT C PIN 3 ****************************************************/

#define PORTC_P3_DIRECTION          PORT_PIN_IN
#define PORTC_P3_MODE               PORT_DIO_MODE
#define PORTC_P3_RESISTOR           OFF
#define PORTC_P3_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P3_DIR_CHANGE         STD_OFF
#define PORTC_P3_MODE_CHANGE        STD_OFF


/****************************** PORT C PIN 4 ****************************************************/

#define PORTC_P4_DIRECTION          PORT_PIN_IN
#define PORTC_P4_MODE               PORT_DIO_MODE
#define PORTC_P4_RESISTOR           OFF
#define PORTC_P4_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P4_DIR_CHANGE         STD_OFF
#define PORTC_P4_MODE_CHANGE        STD_OFF


/****************************** PORT C PIN 5 ****************************************************/

#define PORTC_P5_DIRECTION          PORT_PIN_IN
#define PORTC_P5_MODE               PORT_DIO_MODE
#define PORTC_P5_RESISTOR           OFF
#define PORTC_P5_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P5_DIR_CHANGE         STD_OFF
#define PORTC_P5_MODE_CHANGE        STD_OFF



/****************************** PORT C PIN 6 ****************************************************/

#define PORTC_P6_DIRECTION          PORT_PIN_IN
#define PORTC_P6_MODE               PORT_DIO_MODE
#define PORTC_P6_RESISTOR           OFF
#define PORTC_P6_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P6_DIR_CHANGE         STD_OFF
#define PORTC_P6_MODE_CHANGE        STD_OFF


/****************************** PORT C PIN 7 ****************************************************/

#define PORTC_P7_DIRECTION          PORT_PIN_IN
#define PORTC_P7_MODE               PORT_DIO_MODE
#define PORTC_P7_RESISTOR           OFF
#define PORTC_P7_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTC_P7_DIR_CHANGE         STD_OFF
#define PORTC_P7_MODE_CHANGE        STD_OFF





/****************************** PORT D PIN 0 ****************************************************/

#define PORTD_P0_DIRECTION          PORT_PIN_IN
#define PORTD_P0_MODE               PORT_DIO_MODE
#define PORTD_P0_RESISTOR           OFF
#define PORTD_P0_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P0_DIR_CHANGE         STD_OFF
#define PORTD_P0_MODE_CHANGE        STD_OFF

/****************************** PORT D PIN 1 ****************************************************/

#define PORTD_P1_DIRECTION          PORT_PIN_IN
#define PORTD_P1_MODE               PORT_DIO_MODE
#define PORTD_P1_RESISTOR           OFF
#define PORTD_P1_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P1_DIR_CHANGE         STD_OFF
#define PORTD_P1_MODE_CHANGE        STD_OFF

/****************************** PORT D PIN 2 ****************************************************/

#define PORTD_P2_DIRECTION          PORT_PIN_IN
#define PORTD_P2_MODE               PORT_DIO_MODE
#define PORTD_P2_RESISTOR           OFF
#define PORTD_P2_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P2_DIR_CHANGE         STD_OFF
#define PORTD_P2_MODE_CHANGE        STD_OFF

/****************************** PORT D PIN 3 ****************************************************/

#define PORTD_P3_DIRECTION          PORT_PIN_IN
#define PORTD_P3_MODE               PORT_DIO_MODE
#define PORTD_P3_RESISTOR           OFF
#define PORTD_P3_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P3_DIR_CHANGE         STD_OFF
#define PORTD_P3_MODE_CHANGE        STD_OFF


/****************************** PORT D PIN 4 ****************************************************/

#define PORTD_P4_DIRECTION          PORT_PIN_IN
#define PORTD_P4_MODE               PORT_DIO_MODE
#define PORTD_P4_RESISTOR           OFF
#define PORTD_P4_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P4_DIR_CHANGE         STD_OFF
#define PORTD_P4_MODE_CHANGE        STD_OFF


/****************************** PORT D PIN 5 ****************************************************/

#define PORTD_P5_DIRECTION          PORT_PIN_IN
#define PORTD_P5_MODE               PORT_DIO_MODE
#define PORTD_P5_RESISTOR           OFF
#define PORTD_P5_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P5_DIR_CHANGE         STD_OFF
#define PORTD_P5_MODE_CHANGE        STD_OFF



/****************************** PORT D PIN 6 ****************************************************/

#define PORTD_P6_DIRECTION          PORT_PIN_IN
#define PORTD_P6_MODE               PORT_DIO_MODE
#define PORTD_P6_RESISTOR           OFF
#define PORTD_P6_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P6_DIR_CHANGE         STD_OFF
#define PORTD_P6_MODE_CHANGE        STD_OFF


/****************************** PORT D PIN 7 ****************************************************/

#define PORTD_P7_DIRECTION          PORT_PIN_IN
#define PORTD_P7_MODE               PORT_DIO_MODE
#define PORTD_P7_RESISTOR           OFF
#define PORTD_P7_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTD_P7_DIR_CHANGE         STD_OFF
#define PORTD_P7_MODE_CHANGE        STD_OFF




/****************************** PORT E PIN 0 ****************************************************/

#define PORTE_P0_DIRECTION          PORT_PIN_IN
#define PORTE_P0_MODE               PORT_DIO_MODE
#define PORTE_P0_RESISTOR           OFF
#define PORTE_P0_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTE_P0_DIR_CHANGE         STD_OFF
#define PORTE_P0_MODE_CHANGE        STD_OFF

/****************************** PORT E PIN 1 ****************************************************/

#define PORTE_P1_DIRECTION          PORT_PIN_IN
#define PORTE_P1_MODE               PORT_DIO_MODE
#define PORTE_P1_RESISTOR           OFF
#define PORTE_P1_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTE_P1_DIR_CHANGE         STD_OFF
#define PORTE_P1_MODE_CHANGE        STD_OFF

/****************************** PORT E PIN 2 ****************************************************/

#define PORTE_P2_DIRECTION          PORT_PIN_IN
#define PORTE_P2_MODE               PORT_DIO_MODE
#define PORTE_P2_RESISTOR           OFF
#define PORTE_P2_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTE_P2_DIR_CHANGE         STD_OFF
#define PORTE_P2_MODE_CHANGE        STD_OFF

/****************************** PORT E PIN 3 ****************************************************/

#define PORTE_P3_DIRECTION          PORT_PIN_IN
#define PORTE_P3_MODE               PORT_DIO_MODE
#define PORTE_P3_RESISTOR           OFF
#define PORTE_P3_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTE_P3_DIR_CHANGE         STD_OFF
#define PORTE_P3_MODE_CHANGE        STD_OFF


/****************************** PORT E PIN 4 ****************************************************/

#define PORTE_P4_DIRECTION          PORT_PIN_IN
#define PORTE_P4_MODE               PORT_DIO_MODE
#define PORTE_P4_RESISTOR           OFF
#define PORTE_P4_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTE_P4_DIR_CHANGE         STD_OFF
#define PORTE_P4_MODE_CHANGE        STD_OFF


/****************************** PORT E PIN 5 ****************************************************/

#define PORTE_P5_DIRECTION          PORT_PIN_IN
#define PORTE_P5_MODE               PORT_DIO_MODE
#define PORTE_P5_RESISTOR           OFF
#define PORTE_P5_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTE_P5_DIR_CHANGE         STD_OFF
#define PORTE_P5_MODE_CHANGE        STD_OFF




/****************************** PORT F PIN 0 ****************************************************/

#define PORTF_P0_DIRECTION          PORT_PIN_IN
#define PORTF_P0_MODE               PORT_DIO_MODE
#define PORTF_P0_RESISTOR           OFF
#define PORTF_P0_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTF_P0_DIR_CHANGE         STD_OFF
#define PORTF_P0_MODE_CHANGE        STD_OFF

/****************************** PORT F PIN 1 ****************************************************/

#define PORTF_P1_DIRECTION          PORT_PIN_OUT
#define PORTF_P1_MODE               PORT_DIO_MODE
#define PORTF_P1_RESISTOR           OFF
#define PORTF_P1_LEVEL              PORT_PIN_LEVEL_HIGH
#define PORTF_P1_DIR_CHANGE         STD_OFF
#define PORTF_P1_MODE_CHANGE        STD_OFF

/****************************** PORT F PIN 2 ****************************************************/

#define PORTF_P2_DIRECTION          PORT_PIN_IN
#define PORTF_P2_MODE               PORT_DIO_MODE
#define PORTF_P2_RESISTOR           OFF
#define PORTF_P2_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTF_P2_DIR_CHANGE         STD_OFF
#define PORTF_P2_MODE_CHANGE        STD_OFF

/****************************** PORT F PIN 3 ****************************************************/

#define PORTF_P3_DIRECTION          PORT_PIN_IN
#define PORTF_P3_MODE               PORT_DIO_MODE
#define PORTF_P3_RESISTOR           OFF
#define PORTF_P3_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTF_P3_DIR_CHANGE         STD_OFF
#define PORTF_P3_MODE_CHANGE        STD_OFF


/****************************** PORT F PIN 4 ****************************************************/

#define PORTF_P4_DIRECTION          PORT_PIN_IN
#define PORTF_P4_MODE               PORT_DIO_MODE
#define PORTF_P4_RESISTOR           PULL_UP
#define PORTF_P4_LEVEL              PORT_PIN_LEVEL_LOW
#define PORTF_P4_DIR_CHANGE         STD_OFF
#define PORTF_P4_MODE_CHANGE        STD_OFF





#endif /* PORT_CFG_H_ */
