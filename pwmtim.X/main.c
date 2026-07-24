/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.171.5
        Device            :  dsPIC33CK64MC105
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.10
        MPLAB 	          :  MPLAB X v6.05
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pin_manager.h"

/*
                         Main application
 */
uint16_t count=0;
uint16_t SoftStart_H = 11;
uint16_t SoftStart_L = 5010;
uint8_t dir = 0;


void Timer_Intr()
{
    IFS0bits.T1IF = false;
  
    if (dir == 1)
    {
    count++;     
    SoftStart_H = SoftStart_H + 10;
    if(SoftStart_H>=4800)
    {
        SoftStart_H = 4800;
    }
    
    SoftStart_L = SoftStart_L + 10;
    if(SoftStart_L>=9800)
    {
        SoftStart_L = 9800;
    }
        if (count==1)
    {
        PG2DC = SoftStart_H;
        PG2TRIGB = SoftStart_L;
        PG2STATbits.UPDREQ=1;
        PG2CONLbits.ON = 1;
    }
    else if(count==2)
    {
        PG3DC = SoftStart_H;
        PG3TRIGB = SoftStart_L;
        PG3STATbits.UPDREQ=1; 
        PG3CONLbits.ON = 1;
    }
    else
    {
        count=100;
    PG1DC = SoftStart_H;
    PG1TRIGB = SoftStart_L;
    PG1STATbits.UPDREQ=1;
        
    PG2DC = SoftStart_H;
    PG2TRIGB = SoftStart_L;
    PG2STATbits.UPDREQ=1;
    
    PG3DC = SoftStart_H;
    PG3TRIGB = SoftStart_L;
    PG3STATbits.UPDREQ=1; 
    }
    }
    
    else if (dir == 0)
    {
    SoftStart_H = SoftStart_H - 10;
    if(SoftStart_H<=20)
    {
        SoftStart_H = 11;
    }
    
    SoftStart_L = SoftStart_L - 10;
    if(SoftStart_L<=5111)
    {
        SoftStart_L = 5111;
    }
    
    PG1DC = SoftStart_H;
    PG1TRIGB = SoftStart_L;
    PG1STATbits.UPDREQ=1;
        
    PG2DC = SoftStart_H;
    PG2TRIGB = SoftStart_L;
    PG2STATbits.UPDREQ=1;
    
    PG3DC = SoftStart_H;
    PG3TRIGB = SoftStart_L;
    PG3STATbits.UPDREQ=1; 
    }
    


}
void SW_Intr()
{
    dir = !dir;
}

int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TMR1_SetInterruptHandler(Timer_Intr);
    IO_RB4_SetInterruptHandler(SW_Intr);
    PG1TRIGA=5000;
    PG1TRIGB = SoftStart_H;
    PG1DC = SoftStart_L;
    PG1STATbits.UPDREQ=1;
    PG2TRIGA=5000;
    PG3TRIGA=5000;
    
    while (1)
    {
        // Add your application code
    }
    return 1; 
}
/**
 End of File
*/

