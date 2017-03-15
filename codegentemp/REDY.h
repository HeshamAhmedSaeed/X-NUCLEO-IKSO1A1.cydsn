/*******************************************************************************
* File Name: REDY.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_REDY_H) /* Pins REDY_H */
#define CY_PINS_REDY_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "REDY_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 REDY__PORT == 15 && ((REDY__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    REDY_Write(uint8 value);
void    REDY_SetDriveMode(uint8 mode);
uint8   REDY_ReadDataReg(void);
uint8   REDY_Read(void);
void    REDY_SetInterruptMode(uint16 position, uint16 mode);
uint8   REDY_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the REDY_SetDriveMode() function.
     *  @{
     */
        #define REDY_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define REDY_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define REDY_DM_RES_UP          PIN_DM_RES_UP
        #define REDY_DM_RES_DWN         PIN_DM_RES_DWN
        #define REDY_DM_OD_LO           PIN_DM_OD_LO
        #define REDY_DM_OD_HI           PIN_DM_OD_HI
        #define REDY_DM_STRONG          PIN_DM_STRONG
        #define REDY_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define REDY_MASK               REDY__MASK
#define REDY_SHIFT              REDY__SHIFT
#define REDY_WIDTH              1u

/* Interrupt constants */
#if defined(REDY__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in REDY_SetInterruptMode() function.
     *  @{
     */
        #define REDY_INTR_NONE      (uint16)(0x0000u)
        #define REDY_INTR_RISING    (uint16)(0x0001u)
        #define REDY_INTR_FALLING   (uint16)(0x0002u)
        #define REDY_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define REDY_INTR_MASK      (0x01u) 
#endif /* (REDY__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define REDY_PS                     (* (reg8 *) REDY__PS)
/* Data Register */
#define REDY_DR                     (* (reg8 *) REDY__DR)
/* Port Number */
#define REDY_PRT_NUM                (* (reg8 *) REDY__PRT) 
/* Connect to Analog Globals */                                                  
#define REDY_AG                     (* (reg8 *) REDY__AG)                       
/* Analog MUX bux enable */
#define REDY_AMUX                   (* (reg8 *) REDY__AMUX) 
/* Bidirectional Enable */                                                        
#define REDY_BIE                    (* (reg8 *) REDY__BIE)
/* Bit-mask for Aliased Register Access */
#define REDY_BIT_MASK               (* (reg8 *) REDY__BIT_MASK)
/* Bypass Enable */
#define REDY_BYP                    (* (reg8 *) REDY__BYP)
/* Port wide control signals */                                                   
#define REDY_CTL                    (* (reg8 *) REDY__CTL)
/* Drive Modes */
#define REDY_DM0                    (* (reg8 *) REDY__DM0) 
#define REDY_DM1                    (* (reg8 *) REDY__DM1)
#define REDY_DM2                    (* (reg8 *) REDY__DM2) 
/* Input Buffer Disable Override */
#define REDY_INP_DIS                (* (reg8 *) REDY__INP_DIS)
/* LCD Common or Segment Drive */
#define REDY_LCD_COM_SEG            (* (reg8 *) REDY__LCD_COM_SEG)
/* Enable Segment LCD */
#define REDY_LCD_EN                 (* (reg8 *) REDY__LCD_EN)
/* Slew Rate Control */
#define REDY_SLW                    (* (reg8 *) REDY__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define REDY_PRTDSI__CAPS_SEL       (* (reg8 *) REDY__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define REDY_PRTDSI__DBL_SYNC_IN    (* (reg8 *) REDY__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define REDY_PRTDSI__OE_SEL0        (* (reg8 *) REDY__PRTDSI__OE_SEL0) 
#define REDY_PRTDSI__OE_SEL1        (* (reg8 *) REDY__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define REDY_PRTDSI__OUT_SEL0       (* (reg8 *) REDY__PRTDSI__OUT_SEL0) 
#define REDY_PRTDSI__OUT_SEL1       (* (reg8 *) REDY__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define REDY_PRTDSI__SYNC_OUT       (* (reg8 *) REDY__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(REDY__SIO_CFG)
    #define REDY_SIO_HYST_EN        (* (reg8 *) REDY__SIO_HYST_EN)
    #define REDY_SIO_REG_HIFREQ     (* (reg8 *) REDY__SIO_REG_HIFREQ)
    #define REDY_SIO_CFG            (* (reg8 *) REDY__SIO_CFG)
    #define REDY_SIO_DIFF           (* (reg8 *) REDY__SIO_DIFF)
#endif /* (REDY__SIO_CFG) */

/* Interrupt Registers */
#if defined(REDY__INTSTAT)
    #define REDY_INTSTAT            (* (reg8 *) REDY__INTSTAT)
    #define REDY_SNAP               (* (reg8 *) REDY__SNAP)
    
	#define REDY_0_INTTYPE_REG 		(* (reg8 *) REDY__0__INTTYPE)
#endif /* (REDY__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_REDY_H */


/* [] END OF FILE */
