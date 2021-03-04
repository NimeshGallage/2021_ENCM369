/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    LATA = 0x81;  //Initialize LEDs
    T0CON0 = 0x90; //Set enable, 16-bit, postscaler
    T0CON1 = 0x54; //Set clock source, asynchronous, prescaler

} /* end UserAppInitialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    static u16 su16Counter = 0x0000;
    u8 u8LataValue;
    static u8 su8LataDirection = 0x00;   //0 shifts left, 1 shifts right

    if(su16Counter == 0x01F4)   //if = 500, or 1ms total
    {
        su16Counter = 0x0000;  //reset counter
        u8LataValue = LATA & 0x7F;  //bitmask LATA without Heartbeat LED
        
        if(su8LataDirection == 0x00) //shifting left
        {
            u8LataValue = u8LataValue << 1; 
        }
        
        if(su8LataDirection == 0x01) //shifting right
        {
            u8LataValue = u8LataValue >> 1;
        }
        
        LATA = u8LataValue | 0x80;  //give value back to LATA
        
        if(u8LataValue == 0x20) //furthest left
        {
            su8LataDirection = 1; //direction direction
        }
        
        if(u8LataValue == 0x01) //furthest right
        {
            su8LataDirection = 0; //change direction
        }
    }
    su16Counter++;

} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
