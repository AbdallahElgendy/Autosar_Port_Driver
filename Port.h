 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Abdallah Elgendy
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H




/* Id for the company in the AUTOSAR
 *
 */
#define PORT_VENDOR_ID    (1000U)

/* Port Module Id */
#define PORT_MODULE_ID    (124U)

/* Port Instance Id */
#define PORT_INSTANCE_ID  (0U)



/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)



/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)



/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif



/* Non AUTOSAR files */
#include "Common_Macros.h"


/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* Service ID for PORT Initialization  */
#define PORT_INIT_SID                        (uint8)0x00

/* Service ID for Port Set Pin Direction  */
#define PORT_SET_PIN_DIRECTION_SID           (uint8)0x01

/* Service ID for Port Refresh Port Direction  */
#define PORT_REFRESH_PORT_DIRECTION_SID      (uint8)0x02

/* Service ID for Port Get Version Info   */
#define PORT_GET_VERSION_INFO_SID            (uint8)0x03

/* Service ID for Port Set Pin Mode   */
#define PORT_SET_PIN_MODE_SID                (uint8)0x04



/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/


/* DET code to Invalid Port Pin ID requested  */
#define PORT_E_PARAM_PIN                               (uint8)0x0A

/* DET code to Port Pin not configured as changeable   */
#define PORT_E_DIRECTION_UNCHANGEABLE                  (uint8)0x0B

/* DET code to API Port_Init service called with wrong parameter  */
#define PORT_E_PARAM_CONFIG                            (uint8)0x0C

/* DET code to API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE                      (uint8)0x0D

/* DET code to API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE                       (uint8)0x0E

/* DET code to API service called without module initialization */
#define PORT_E_UNINIT                                  (uint8)0x0F

/* DET code to APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                           (uint8)0x10



/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/*
 * Description: Data type for the symbolic name of a port pin.
 */
typedef uint8 Port_PinType  ;


/*
 * Description: Different port pin modes.
 */
typedef uint8 Port_PinModeType  ;



/*
 * Description:  port number.
 */
typedef uint8 Port_PortID  ;



/* Description: Enum to hold PIN direction */
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
}Port_PinDirectionType;


/* Description: Enum to hold PIN level value */
typedef enum
{
    PORT_PIN_LEVEL_LOW ,
    PORT_PIN_LEVEL_HIGH
}Port_PinLevelValue;



/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;



/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *  3. the direction of pin --> INPUT or OUTPUT
 *  4. the internal resistor --> Disable, Pull up or Pull down
 *  5. the pin mode type ---> GPIO , ADC .. etc
 *  6. the pin level --> LOW , HIGH
 *  7. pin_dir_change --> pin direction changeable  , STD_ON / STD_OFF
 *  8. pin_mode_change --> pin mode changeable    , STD_ON / STD_OFF
 */
typedef struct 
{
    Port_PortID port_num;
    Port_PinType pin_num;
    Port_PinDirectionType direction;
    Port_InternalResistor resistor;
    Port_PinModeType pin_mode;
    Port_PinLevelValue level ;
    uint8 pin_dir_change ;
    uint8 pin_mode_change ;

}Port_ConfigPin;

typedef struct
{
    Port_ConfigPin pins[PORT_CONFIGURED_PINS] ;

}Port_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Initialize the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)  ;




#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to set the port pin direction
************************************************************************************/
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction) ;
#endif


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to refresh port direction
************************************************************************************/
void Port_RefreshPortDirection(void)  ;



#if (PORT_VERSION_INFO_API == STD_ON)
/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module.
* Return value: None
* Description: Function to return the version information of this module
************************************************************************************/
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo) ;
#endif



#if (PORT_SET_PIN_MODE_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: reentrant
*  Parameters (in): Pin - Port Pin ID number
*                  Mode - New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Set the port pin mode
************************************************************************************/
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
#endif





/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures  */
extern const Port_ConfigType Port_Configuration;

















/************************************************************************************
* Service Name: Port_SetupGpioPin
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Function to Setup the pin configuration:
*              - Setup the pin as Digital GPIO pin
*              - Setup the direction of the GPIO pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
void Port_SetupGpioPin(const Port_ConfigType *ConfigPtr );

#endif /* PORT_H */
