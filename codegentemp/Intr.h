/*******************************************************************************
* File Name: Intr.h  
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

#if !defined(CY_PINS_Intr_H) /* Pins Intr_H */
#define CY_PINS_Intr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Intr_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Intr__PORT == 15 && ((Intr__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Intr_Write(uint8 value);
void    Intr_SetDriveMode(uint8 mode);
uint8   Intr_ReadDataReg(void);
uint8   Intr_Read(void);
void    Intr_SetInterruptMode(uint16 position, uint16 mode);
uint8   Intr_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Intr_SetDriveMode() function.
     *  @{
     */
        #define Intr_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Intr_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Intr_DM_RES_UP          PIN_DM_RES_UP
        #define Intr_DM_RES_DWN         PIN_DM_RES_DWN
        #define Intr_DM_OD_LO           PIN_DM_OD_LO
        #define Intr_DM_OD_HI           PIN_DM_OD_HI
        #define Intr_DM_STRONG          PIN_DM_STRONG
        #define Intr_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Intr_MASK               Intr__MASK
#define Intr_SHIFT              Intr__SHIFT
#define Intr_WIDTH              1u

/* Interrupt constants */
#if defined(Intr__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Intr_SetInterruptMode() function.
     *  @{
     */
        #define Intr_INTR_NONE      (uint16)(0x0000u)
        #define Intr_INTR_RISING    (uint16)(0x0001u)
        #define Intr_INTR_FALLING   (uint16)(0x0002u)
        #define Intr_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Intr_INTR_MASK      (0x01u) 
#endif /* (Intr__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Intr_PS                     (* (reg8 *) Intr__PS)
/* Data Register */
#define Intr_DR                     (* (reg8 *) Intr__DR)
/* Port Number */
#define Intr_PRT_NUM                (* (reg8 *) Intr__PRT) 
/* Connect to Analog Globals */                                                  
#define Intr_AG                     (* (reg8 *) Intr__AG)                       
/* Analog MUX bux enable */
#define Intr_AMUX                   (* (reg8 *) Intr__AMUX) 
/* Bidirectional Enable */                                                        
#define Intr_BIE                    (* (reg8 *) Intr__BIE)
/* Bit-mask for Aliased Register Access */
#define Intr_BIT_MASK               (* (reg8 *) Intr__BIT_MASK)
/* Bypass Enable */
#define Intr_BYP                    (* (reg8 *) Intr__BYP)
/* Port wide control signals */                                                   
#define Intr_CTL                    (* (reg8 *) Intr__CTL)
/* Drive Modes */
#define Intr_DM0                    (* (reg8 *) Intr__DM0) 
#define Intr_DM1                    (* (reg8 *) Intr__DM1)
#define Intr_DM2                    (* (reg8 *) Intr__DM2) 
/* Input Buffer Disable Override */
#define Intr_INP_DIS                (* (reg8 *) Intr__INP_DIS)
/* LCD Common or Segment Drive */
#define Intr_LCD_COM_SEG            (* (reg8 *) Intr__LCD_COM_SEG)
/* Enable Segment LCD */
#define Intr_LCD_EN                 (* (reg8 *) Intr__LCD_EN)
/* Slew Rate Control */
#define Intr_SLW                    (* (reg8 *) Intr__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Intr_PRTDSI__CAPS_SEL       (* (reg8 *) Intr__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Intr_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Intr__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Intr_PRTDSI__OE_SEL0        (* (reg8 *) Intr__PRTDSI__OE_SEL0) 
#define Intr_PRTDSI__OE_SEL1        (* (reg8 *) Intr__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Intr_PRTDSI__OUT_SEL0       (* (reg8 *) Intr__PRTDSI__OUT_SEL0) 
#define Intr_PRTDSI__OUT_SEL1       (* (reg8 *) Intr__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Intr_PRTDSI__SYNC_OUT       (* (reg8 *) Intr__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Intr__SIO_CFG)
    #define Intr_SIO_HYST_EN        (* (reg8 *) Intr__SIO_HYST_EN)
    #define Intr_SIO_REG_HIFREQ     (* (reg8 *) Intr__SIO_REG_HIFREQ)
    #define Intr_SIO_CFG            (* (reg8 *) Intr__SIO_CFG)
    #define Intr_SIO_DIFF           (* (reg8 *) Intr__SIO_DIFF)
#endif /* (Intr__SIO_CFG) */

/* Interrupt Registers */
#if defined(Intr__INTSTAT)
    #define Intr_INTSTAT            (* (reg8 *) Intr__INTSTAT)
    #define Intr_SNAP               (* (reg8 *) Intr__SNAP)
    
	#define Intr_0_INTTYPE_REG 		(* (reg8 *) Intr__0__INTTYPE)
#endif /* (Intr__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Intr_H */


/* [] END OF FILE */
