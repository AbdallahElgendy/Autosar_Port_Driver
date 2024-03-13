 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Port.h"
#include "tm4c123gh6pm_registers.h"
#include "Port_Regs.h"


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif


STATIC const Port_ConfigPin * Port_Pins = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;




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
void Port_Init(const Port_ConfigType* ConfigPtr)  {

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        Port_Pins = ConfigPtr->pins ;
        Port_Status = PORT_INITIALIZED ;
        uint8 idx ;
        for(idx= ZERO ; idx <PORT_CONFIGURED_PINS ; idx++){

                volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
                volatile uint32 clock_var = 0;

                switch(Port_Pins[idx].port_num)
                {
                    case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                             break;
                    case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                             break;
                    case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                             break;
                    case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                             break;
                    case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                             break;
                    case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                             break;
                }

                /* Enable clock for PORT */
                SYSCTL_RCGCGPIO_REG |= (1<<Port_Pins[idx].port_num);
                clock_var = SYSCTL_RCGCGPIO_REG;


                /*Unlocking locked pins */
                if( ((Port_Pins[idx].port_num == PORT_D) && (Port_Pins[idx].pin_num== PORT_P7)) || ((Port_Pins[idx].port_num == PORT_F) && (Port_Pins[idx].pin_num == PORT_P0)) ) /* PD7 or PF0 */
                {
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = UNLOCK_VALUE;                        /* Unlock the GPIOCR register */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) ,Port_Pins[idx].pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
                }
                /* Save JTAG pins*/
                else if((Port_Pins[idx].port_num== PORT_C) && ((Port_Pins[idx].pin_num >= PORT_P0 ) || (Port_Pins[idx].pin_num <=PORT_P3 ) )) /* PC0 to PC3 */
                {
                    /* Do Nothing ...  this is the JTAG pins */
                }
                else
                {
                    /* Do Nothing ... No need to unlock the commit register for this pin */
                }



                /* Initialize the mode */
                if(Port_Pins[idx].pin_mode == PORT_DIO_MODE){

                    /* Setup the pin mode as GPIO */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins[idx].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins[idx].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[idx].pin_num * 4));     /* Clear the PMCx bits for this pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins[idx].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


                    /* Initialize the direction */
                       if(Port_Pins[idx].direction == PORT_PIN_OUT)
                       {
                           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins[idx].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                           if(Port_Pins[idx].level == PORT_PIN_LEVEL_HIGH)
                           {
                               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins[idx].pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                           }
                           else
                           {
                               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , Port_Pins[idx].pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                           }
                       }
                       else if(Port_Pins[idx].direction == PORT_PIN_IN)
                       {
                           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  Port_Pins[idx].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                           if( Port_Pins[idx].resistor == PULL_UP)
                           {
                               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins[idx].pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                           }
                           else if(Port_Pins[idx].resistor == PULL_DOWN)
                           {
                               SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) ,  Port_Pins[idx].pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                           }
                           else
                           {
                               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Pins[idx].pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                               CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Pins[idx].pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                           }
                       }
                       else
                       {
                           /* Do Nothing */
                       }

                }
                else if (Port_Pins[idx].pin_mode == PORT_ALTER_FUNC_ADC_MODE){
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins[idx].pin_num);          /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins[idx].pin_num);         /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                        if(Port_Pins[idx].direction == PORT_PIN_OUT)
                        {
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins[idx].pin_num);                  /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                        }
                        else if(Port_Pins[idx].direction == PORT_PIN_IN)
                        {
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  Port_Pins[idx].pin_num);               /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                        }
                        else
                        {
                            /* Do Nothing */
                        }

                }
                else{
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,  Port_Pins[idx].pin_num);            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,  Port_Pins[idx].pin_num);                     /* enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (( Port_Pins[idx].pin_num) * 4));         /* Clear the PMCx bits for this pin */
                        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Port_Pins[idx].pin_mode<< (( Port_Pins[idx].pin_num)* 4));  /* Set the PMCx bits for this pin to the selected Alternate function in the configurations */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,  Port_Pins[idx].pin_num);               /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


                }
           }

      }

 }





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
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction) {
    boolean error = FALSE;

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE ;
    }
    else{
        /* No thing */
    }

    /* Check if Invalid Port Pin ID requested  */
    if (PORT_CONFIGURED_PINS <= Pin)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE ;
    }
    else{
        /* No thing */
    }

    /* Check if Port Pin not configured as changeable */
    if (STD_OFF == Port_Pins[Pin].pin_dir_change)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE ;
    }
    else{
        /* No thing */
    }
#endif
    if (FALSE == error){
        volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        switch(Port_Pins[Pin].port_num)
        {
            case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                     break;
            case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                     break;
            case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                     break;
            case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                     break;
            case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                     break;
            case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                     break;
        }

        /*Preventing any actions to be done upon JTAG pins*/
        if((Port_Pins[Pin].port_num== PORT_C) && ((Port_Pins[Pin].pin_num >= PORT_P0 ) || (Port_Pins[Pin].pin_num <=PORT_P3 ) )) /* PC0 to PC3 */
        {
           /* Do Nothing ...  this is the JTAG pins */
        }
        else
        {
            if(Direction == PORT_PIN_OUT)
            {
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins[Pin].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

            }
            else if(Direction == PORT_PIN_IN)
            {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  Port_Pins[Pin].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

            }
            else
            {
              /* Do Nothing */
            }
        }

    }
    else
    {
        /* No thing */
    }


}
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
void Port_RefreshPortDirection(void) {
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == Port_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE ;
    }
    else{
        /* No thing */
    }

#endif
    if (FALSE == error){
        uint8 idx ;
        for (idx =ZERO ; idx <PORT_CONFIGURED_PINS ; idx++){
            volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
            switch(Port_Pins[idx].port_num)
            {
                case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                         break;
                case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                         break;
                case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                         break;
                case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                         break;
                case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                         break;
                case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                         break;
            }

            /*Preventing any actions to be done upon JTAG pins*/
            if((Port_Pins[idx].port_num== PORT_C) && ((Port_Pins[idx].pin_num >= PORT_P0 ) || (Port_Pins[idx].pin_num <=PORT_P3 ) )) /* PC0 to PC3 */
            {
               /* Do Nothing ...  this is the JTAG pins */
            }
            else
            {
                if(STD_OFF == Port_Pins[idx].pin_dir_change){
                    if(PORT_PIN_OUT == Port_Pins[idx].direction)
                       {
                         SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Pins[idx].pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                       }
                       else if(PORT_PIN_IN == Port_Pins[idx].direction)
                       {
                         CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) ,  Port_Pins[idx].pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                       }
                       else
                       {
                         /* Do Nothing */
                       }
                }
                else
                {
                    /* No thing */
                }
            }
        }

    }
    else
    {
        /* No thing */
    }


}





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
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo) {
    boolean error = FALSE;
 #if (PORT_DEV_ERROR_DETECT == STD_ON)
     /* Check if the Driver is initialized before using this function */
     if (PORT_NOT_INITIALIZED == Port_Status)
     {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
         error = TRUE ;
     }
     /* check if the input configuration pointer is not a NULL_PTR */
     if (NULL_PTR == versioninfo)
     {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
         error = TRUE ;
     }
     else{
         /* No thing */
     }

 #endif
     if (FALSE == error){

         /* read the vendor Id */
          versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
          /* read the module Id */
          versioninfo->moduleID = (uint16)PORT_MODULE_ID;
          /* read Software Major Version */
          versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
          /* read Software Minor Version */
          versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
          /* read Software Patch Version */
          versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;


     }
     else
     {
         /* No thing */
     }


}
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
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode){
    boolean error = FALSE;

 #if (PORT_DEV_ERROR_DETECT == STD_ON)
     /* Check if the Driver is initialized before using this function */
     if (PORT_NOT_INITIALIZED == Port_Status)
     {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
         error = TRUE ;
     }
     else{
         /* No thing */
     }

     /* Check if Invalid Port Pin ID requested  */
     if (Pin >= PORT_CONFIGURED_PINS)
     {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
         error = TRUE ;
     }
     else{
         /* No thing */
     }

     /* Check if Port Pin Mode passed not valid  */
     if (Mode >= PORT_ALTER_FUNC_ADC_MODE)
     {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
         error = TRUE ;
     }
     else{
         /* No thing */
     }

     /* Check if Port Pin not configured as changeable */
     if (STD_OFF == Port_Pins[Pin].pin_dir_change)
     {
         Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_DIRECTION_UNCHANGEABLE);
         error = TRUE ;
     }
     else{
         /* No thing */
     }
 #endif
     if (FALSE == error){
         volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
         switch(Port_Pins[Pin].port_num)
         {
             case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                      break;
             case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                      break;
             case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                      break;
             case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                      break;
             case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                      break;
             case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                      break;
         }

         /*Preventing any actions to be done upon JTAG pins*/
         if((Port_Pins[Pin].port_num== PORT_C) && ((Port_Pins[Pin].pin_num >= PORT_P0 ) || (Port_Pins[Pin].pin_num <=PORT_P3 ) )) /* PC0 to PC3 */
         {
            /* Do Nothing ...  this is the JTAG pins */
         }
         else
         {
             if(Port_Pins[Pin].pin_mode == PORT_DIO_MODE){
                 /* Setup the pin mode as GPIO */
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins[Pin].pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins[Pin].pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[Pin].pin_num * 4));     /* Clear the PMCx bits for this pin */
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins[Pin].pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

                 }
             else if (Port_Pins[Pin].pin_mode == PORT_ALTER_FUNC_ADC_MODE){
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins[Pin].pin_num);          /* Set the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Pins[Pin].pin_num);         /* Clear the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

             }
             else{
                 CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,  Port_Pins[Pin].pin_num);            /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,  Port_Pins[Pin].pin_num);                     /* enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (( Port_Pins[Pin].pin_num) * 4));         /* Clear the PMCx bits for this pin */
                 *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Port_Pins[Pin].pin_mode<< (( Port_Pins[Pin].pin_num)* 4));  /* Set the PMCx bits for this pin to the selected Alternate function in the configurations */
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,  Port_Pins[Pin].pin_num);               /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */


             }
         }

     }
     else
     {
         /* No thing */
     }

}
#endif















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
*              - Provide initial value for o/p pin
*              - Setup the internal resistor for i/p pin
************************************************************************************/
//void Port_SetupGpioPin(const Port_ConfigType * ConfigPtr )
//{
//    volatile uint32 * PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
//
//    switch(ConfigPtr->port_num)
//    {
//        case  0: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
//		         break;
//     	case  1: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
//		         break;
//	    case  2: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
//		         break;
//	    case  3: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
//		         break;
//        case  4: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
//		         break;
//        case  5: PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
//		         break;
//    }
//
//    if( ((ConfigPtr->port_num == 3) && (ConfigPtr->pin_num == 7)) || ((ConfigPtr->port_num == 5) && (ConfigPtr->pin_num == 0)) ) /* PD7 or PF0 */
//    {
//        *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
//        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , ConfigPtr->pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
//    }
//    else if( (ConfigPtr->port_num == 2) && (ConfigPtr->pin_num <= 3) ) /* PC0 to PC3 */
//    {
//        /* Do Nothing ...  this is the JTAG pins */
//    }
//    else
//    {
//        /* Do Nothing ... No need to unlock the commit register for this pin */
//    }
//
//    if(ConfigPtr->direction == PORT_PIN_OUT)
//    {
//	    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->pin_num);               /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
//
//        if(ConfigPtr->initial_value == STD_HIGH)
//        {
//            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
//        }
//        else
//        {
//            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , ConfigPtr->pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
//        }
//    }
//    else if(ConfigPtr->direction == PORT_PIN_IN)
//    {
//        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , ConfigPtr->pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
//
//        if(ConfigPtr->resistor == PULL_UP)
//        {
//            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
//        }
//        else if(ConfigPtr->resistor == PULL_DOWN)
//        {
//            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
//        }
//        else
//        {
//            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , ConfigPtr->pin_num);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
//            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , ConfigPtr->pin_num);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
//        }
//    }
//    else
//    {
//        /* Do Nothing */
//    }
//
//    /* Setup the pin mode as GPIO */
//    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , ConfigPtr->pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
//    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , ConfigPtr->pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
//    *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (ConfigPtr->pin_num * 4));     /* Clear the PMCx bits for this pin */
//    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , ConfigPtr->pin_num);         /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
//
//}
