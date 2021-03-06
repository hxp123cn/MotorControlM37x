/**
 *******************************************************************************
 * @file    tmpm370_adc.c
 * @brief   This file provides API functions for ADC driver.
 * @version V2.0.2.1
 * @date    2011/01/24
 *
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". TOSHIBA
 * CORPORATION MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. TOSHIBA CORPORATION
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 *
 * TOSHIBA CORPORATION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 *
 * (C)Copyright TOSHIBA CORPORATION 2011 All rights reserved
 *******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "tmpm370_adc.h"

#if defined(__TMPM370_ADC_H)
/** @addtogroup TX03_Periph_Driver
  * @{
  */

/** @defgroup ADC
  * @brief ADC driver modules
  * @{
  */

/** @defgroup ADC_Private_Defines
  * @{
  */

#define ADC_MASK_KEEP1BIT       (uint32_t)0x01U
#define ADC_MASK_KEEP2BITS      (uint32_t)0x03U
#define ADC_MASK_KEEP3BITS      (uint32_t)0x07U
#define ADC_MASK_KEEP4BITS      (uint32_t)0x0FU
#define ADC_MASK_KEEP5BITS      (uint32_t)0x1FU
#define ADC_MASK_KEEP6BITS      (uint32_t)0x3FU
#define ADC_MASK_KEEP7BITS      (uint32_t)0x7FU
#define ADC_MASK_KEEP8BITS      (uint32_t)0xFFU

#define ADC_MOD3_FIX            (0x00000560UL)

#define ADC_TRG_REG_MASK        (0x000000FFUL)

/** @} */
/* End of group ADC_Private_Defines */

/** @defgroup ADC_Private_FunctionPrototypes
  * @{
  */

/** @} */
/* End of group ADC_Private_FunctionPrototypes */

/** @defgroup ADC_Private_Functions
  * @{
  */


static const volatile uint32_t *const ADA_REGx_Address[12U] = {
    &TSB_ADA->REG0, &TSB_ADA->REG1, &TSB_ADA->REG2, &TSB_ADA->REG3,
    &TSB_ADA->REG4, &TSB_ADA->REG5, &TSB_ADA->REG6, &TSB_ADA->REG7,
    &TSB_ADA->REG8, &TSB_ADA->REG9, &TSB_ADA->REG10, &TSB_ADA->REG11
};

static const volatile uint32_t *const ADB_REGx_Address[12U] = {
    &TSB_ADB->REG0, &TSB_ADB->REG1, &TSB_ADB->REG2, &TSB_ADB->REG3,
    &TSB_ADB->REG4, &TSB_ADB->REG5, &TSB_ADB->REG6, &TSB_ADB->REG7,
    &TSB_ADB->REG8, &TSB_ADB->REG9, &TSB_ADB->REG10, &TSB_ADB->REG11
};

static volatile uint32_t *const ADA_PSELx_Address[12U] = {
    &TSB_ADA->PSEL0, &TSB_ADA->PSEL1, &TSB_ADA->PSEL2, &TSB_ADA->PSEL3,
    &TSB_ADA->PSEL4, &TSB_ADA->PSEL5, &TSB_ADA->PSEL6, &TSB_ADA->PSEL7,
    &TSB_ADA->PSEL8, &TSB_ADA->PSEL9, &TSB_ADA->PSEL10, &TSB_ADA->PSEL11
};

static volatile uint32_t *const ADB_PSELx_Address[12U] = {
    &TSB_ADB->PSEL0, &TSB_ADB->PSEL1, &TSB_ADB->PSEL2, &TSB_ADB->PSEL3,
    &TSB_ADB->PSEL4, &TSB_ADB->PSEL5, &TSB_ADB->PSEL6, &TSB_ADB->PSEL7,
    &TSB_ADB->PSEL8, &TSB_ADB->PSEL9, &TSB_ADB->PSEL10, &TSB_ADB->PSEL11
};

static volatile uint32_t *const ADA_PSETx_Address[6U] = {
    &TSB_ADA->PSET0, &TSB_ADA->PSET1, &TSB_ADA->PSET2,
    &TSB_ADA->PSET3, &TSB_ADA->PSET4, &TSB_ADA->PSET5
};

static volatile uint32_t *const ADB_PSETx_Address[6U] = {
    &TSB_ADB->PSET0, &TSB_ADB->PSET1, &TSB_ADB->PSET2,
    &TSB_ADB->PSET3, &TSB_ADB->PSET4, &TSB_ADB->PSET5
};

/** @} */
/* End of group ADC_Private_Functions */


/** @defgroup ADC_Exported_Functions
  * @{
  */

/**
  * @brief  Set ADC prescaler output(SCLK) of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  Sample_HoldTime: Select ADC sample hold time.
  *   This parameter can be one of the following values:
  *     ADC_HOLD_FIX
  * @param  Prescaler_Output: Select ADC prescaler output.
  *   This parameter can be one of the following values:
  *     ADC_FC_DIVIDE_LEVEL_NONE, ADC_FC_DIVIDE_LEVEL_2, 
  *     ADC_FC_DIVIDE_LEVEL_4, ADC_FC_DIVIDE_LEVEL_8,
  *     ADC_FC_DIVIDE_LEVEL_16
  * @retval None.
  */
void ADC_SetClk(TSB_AD_TypeDef * ADx, uint32_t Sample_HoldTime, ADC_PRESCALER Prescaler_Output)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_SAMPLEHOLD(Sample_HoldTime));
    assert_param(IS_ADC_PRESCALER(Prescaler_Output));

    tmp = Sample_HoldTime | Prescaler_Output;
    ADx->CLK = tmp;
}


/**
  * @brief  Enable the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @retval None
  */
void ADC_Enable(TSB_AD_TypeDef * ADx)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));

    /* bit0 of MOD0 must be written '0'  */
    tmp |= (uint32_t) (0x01U << 1U);    /* then set bit1(.DACON) of ADxMOD0 */
    ADx->MOD0 = tmp;

    tmp = ADx->MOD1 & (ADC_MASK_KEEP1BIT << 0U);        /* only keep bit0,  */
    tmp |= (uint32_t) (0x01U << 7U);    /* then set bit7(.ADEN)  of ADxMOD1 */
    ADx->MOD1 = tmp;

    ADx->MOD3 = ADC_MOD3_FIX;
}


/**
  * @brief  Disable the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @retval None
  */
void ADC_Disable(TSB_AD_TypeDef * ADx)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));

    /* write '0' to bit1 and bit0 of MOD0 */
    ADx->MOD0 = tmp;

    tmp = ADx->MOD1 & (ADC_MASK_KEEP1BIT << 0U);        /* only keep bit0 of MOD1  */
    ADx->MOD1 = tmp;
}


/**
  * @brief  Start the specified ADC unit with software trigger or constant trigger.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  Trg: Select trigger type.
  *   This parameter can be one of the following values:
  *     ADC_TRG_SW, ADC_TRG_CONSTANT
  * @retval None
  */
void ADC_Start(TSB_AD_TypeDef * ADx, ADC_TrgType Trg)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_START(Trg));

    if (Trg == ADC_TRG_SW) {
        tmp = ADx->MOD0 & (ADC_MASK_KEEP1BIT << 1U);    /* only keep bit1, */
        tmp |= (uint32_t) (0x01U << 0U);        /* then set ADMOD0.ADSS (_MOD0.bit0) */
        ADx->MOD0 = tmp;
    } else {                    /* ADC_TRG_CONSTANT */
        tmp = ADx->MOD1 & (ADC_MASK_KEEP1BIT << 7U);    /* only keep bit7, */
        tmp |= (uint32_t) (0x01U << 0U);        /* then set ADMOD1.ADAS (_MOD1.bit0) */
        ADx->MOD1 = tmp;
    }
}


/**
  * @brief  Stop the specified ADC unit when use constant trigger.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @retval None
  */
void ADC_StopConstantTrg(TSB_AD_TypeDef * ADx)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));

    /* Clear ADxMOD1<ADAS> */
    tmp = ADx->MOD1 & (ADC_MASK_KEEP1BIT << 7U);        /* only keep bit7 */
    ADx->MOD1 = tmp;
}


/**
  * @brief  Get the conversion state of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  Trg: Select trigger type.
  *   This parameter can be one of the following values:
  *     ADC_TRG_SW, ADC_TRG_CONSTANT, ADC_TRG_TIMER, ADC_TRG_PMD
  * @retval ADC conversion state.
  *   The value returned can be one of the followings:
  *     DONE, BUSY.
  */
WorkState ADC_GetConvertState(TSB_AD_TypeDef * ADx, ADC_TrgType Trg)
{
    WorkState ret = DONE;
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_TRGTYPE(Trg));

    tmp = ADx->MOD2;
    if (Trg == ADC_TRG_SW) {
        tmp &= (ADC_MASK_KEEP1BIT << 1U);       /* only keep bit1 */
    } else {
        tmp &= (ADC_MASK_KEEP1BIT << 0U);       /* only keep bit0 */
    }

    if (tmp) {
        ret = BUSY;
    } else {
        /* do nothing */
    }

    return ret;
}


/**
  * @brief  Set the monitor function of the specified ADC unit and enable it.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  Monitor: The structure containing ADC Monitor configuration
  *         Refer to the members of ADC_MonitorTypeDef in .h file for more detail usage.
  * @retval None
  */
void ADC_SetMonitor(TSB_AD_TypeDef * ADx, ADC_MonitorTypeDef * Monitor)
{
    uint32_t tmp = 0U;
    uint32_t tmpComp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_POINTER_NOT_NULL(Monitor));
    assert_param(IS_ADC_CMPCRx(Monitor->CMPCRx));
    assert_param(IS_ADC_REGx(Monitor->ResultREGx));
    assert_param(IS_ADC_CMPTIMES(Monitor->CmpTimes));
    assert_param(IS_ADC_CMPCONDITION(Monitor->Condition));
    assert_param(IS_ADC_CMPVALUE_12BIT(Monitor->CmpValue));

    tmpComp = Monitor->CmpValue << 4U;  /* 12bit mode: use bit15 to bit4 */

    tmp |= (uint32_t) Monitor->ResultREGx;
    tmp |= (uint32_t) Monitor->Condition << 4U;
    tmp |= (uint32_t) (Monitor->CmpTimes - 1U) << 8U;

    tmp |= (uint32_t) (0x01U << 7U);    /* set bit 7: ADxCMPCRn<CMPnEN> to enable Monitor function */

    if (Monitor->CMPCRx == ADC_CMPCR_0) {
        ADx->CMPCR0 = tmp;
        ADx->CMP0 = tmpComp;
    } else {
        ADx->CMPCR1 = tmp;
        ADx->CMP1 = tmpComp;
    }
}


/**
  * @brief  Disable the monitor function of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  CMPCRx: Select which compare control register will be used.
  *   This parameter can be one of the following values:
  *     ADC_CMPCR_0, ADC_CMPCR_1
  * @retval None
  */
void ADC_DisableMonitor(TSB_AD_TypeDef * ADx, ADC_CMPCRx CMPCRx)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_CMPCRx(CMPCRx));

    if (CMPCRx == ADC_CMPCR_0) {
        /* read CMPCR0 then only keep bit4 to bit0, bit11 to bit8 */
        tmp = ADx->CMPCR0 & ((ADC_MASK_KEEP5BITS << 0U) | (ADC_MASK_KEEP4BITS << 8U));
        ADx->CMPCR0 = tmp;
    } else {
        /* read CMPCR1 then only keep bit4 to bit0, bit11 to bit8 */
        tmp = ADx->CMPCR1 & ((ADC_MASK_KEEP5BITS << 0U) | (ADC_MASK_KEEP4BITS << 8U));
        ADx->CMPCR1 = tmp;
    }
}

/**
  * @brief  Enable the monitor function of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     For M370:   TSB_ADA, TSB_ADB
  *     For M372/3/4:  TSB_ADB
  * @param  CMPCRx: Select which compare control register will be used.
  *   This parameter can be one of the following values:
  *     ADC_CMPCR_0, ADC_CMPCR_1
  * @retval None
  */
void ADC_EnableMonitor(TSB_AD_TypeDef * ADx, ADC_CMPCRx CMPCRx)
{
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_CMPCRx(CMPCRx));

    if (CMPCRx == ADC_CMPCR_0) {
        /* read CMPCR0 then only keep bit4 to bit0, bit11 to bit8 */
        tmp = ADx->CMPCR0 & ((ADC_MASK_KEEP5BITS << 0U) | (ADC_MASK_KEEP4BITS << 8U));
        ADx->CMPCR0 = tmp | (1<<7);
    } else {
        /* read CMPCR1 then only keep bit4 to bit0, bit11 to bit8 */
        tmp = ADx->CMPCR1 & ((ADC_MASK_KEEP5BITS << 0U) | (ADC_MASK_KEEP4BITS << 8U));
        ADx->CMPCR1 = tmp | (1<<7);
    }
}

/**
  * @brief  Get result from the specified AD Conversion Result Register.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  ResultREGx: Select which ADC result register will be read.
  *   This parameter can be one of the following values:
  *     ADC_REG0, ADC_REG1, ADC_REG2, ADC_REG3, ADC_REG4, ADC_REG5,
  *     ADC_REG6, ADC_REG7, ADC_REG8, ADC_REG9, ADC_REG10, ADC_REG11
  * @retval A union with AD result and 2 bits extra information.
  *         Refer to the members of ADC_Result in .h file for more detail usage.
  */
ADC_Result ADC_GetConvertResult(TSB_AD_TypeDef * ADx, ADC_REGx ResultREGx)
{
    ADC_Result result = { 0U };

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_REGx(ResultREGx));

    /* read out result register wanted */
    if (ADx == TSB_ADA) {
        result.All = *(ADA_REGx_Address[ResultREGx]);
    } else {
        result.All = *(ADB_REGx_Address[ResultREGx]);
    }

    result.All &= 0x0000FFFFU;  /* only keep bit15 to bit0 */

    return result;
}


/**
  * @brief  Set the program to be started by each of trigger inputs PMD0 to PMD11
  *         of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  SELx : Specify the "trigger program number select register"
  *   This parameter can be one of the following values:  
  *     PMD_TRG_PROG_SEL0, PMD_TRG_PROG_SEL1, PMD_TRG_PROG_SEL2,
  *     PMD_TRG_PROG_SEL3, PMD_TRG_PROG_SEL4, PMD_TRG_PROG_SEL5,
  *     PMD_TRG_PROG_SEL6, PMD_TRG_PROG_SEL7, PMD_TRG_PROG_SEL8,
  *     PMD_TRG_PROG_SEL9, PMD_TRG_PROG_SEL10, PMD_TRG_PROG_SEL11
  * @param  MacroProgNum : Program number to be selected, together with its Enabled or Disabled setting through a macro
  *   This parameter must be inputed with macro as the format below:
  *     TRG_ENABLE(x), TRG_DISABLE(x).
  *   'x' above can be one of the following values:
  *     PMD_PROG0, PMD_PROG1, PMD_PROG2,
  *     PMD_PROG3, PMD_PROG4, PMD_PROG5
  * @retval None
  */
void ADC_SelectPMDTrgProgNum(TSB_AD_TypeDef * ADx, PMD_TRG_PROG_SELx SELx, uint8_t MacroProgNum)
{
    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_PMD_TRG_PROG_SELx(SELx));
    assert_param(IS_PMD_PROGx_ENABLE_DISABLE(MacroProgNum));

    if (ADx == TSB_ADA) {
        /* currently ADAPSELn is defined as uint32_t */
        *(ADA_PSELx_Address[SELx]) = (uint32_t) MacroProgNum;
    } else {
        /* currently ADBPSELn is defined as uint32_t */
        *(ADB_PSELx_Address[SELx]) = (uint32_t) MacroProgNum;
    }
}


/**
  * @brief  Select the interrupt to be generated for each of programs 0 to 5
  *         of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  TrgProgINT: The structure containing interrupt configuration for all of PMD Trigger Programs
  *         Refer the members of PMD_TrgProgINTTypeDef in .h file for more detail usage.
  * @retval None
  */
void ADC_SetPMDTrgProgINT(TSB_AD_TypeDef * ADx, const PMD_TrgProgINTTypeDef * TrgProgINT)
{
    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_POINTER_NOT_NULL(TrgProgINT));
    assert_param(IS_PMD_INT_NAME(TrgProgINT->INTProg0));
    assert_param(IS_PMD_INT_NAME(TrgProgINT->INTProg1));
    assert_param(IS_PMD_INT_NAME(TrgProgINT->INTProg2));
    assert_param(IS_PMD_INT_NAME(TrgProgINT->INTProg3));
    assert_param(IS_PMD_INT_NAME(TrgProgINT->INTProg4));
    assert_param(IS_PMD_INT_NAME(TrgProgINT->INTProg5));

    /* currently ADxPINTSn is defined as uint32_t */
    ADx->PINTS0 = (uint32_t) TrgProgINT->INTProg0;
    ADx->PINTS1 = (uint32_t) TrgProgINT->INTProg1;
    ADx->PINTS2 = (uint32_t) TrgProgINT->INTProg2;
    ADx->PINTS3 = (uint32_t) TrgProgINT->INTProg3;
    ADx->PINTS4 = (uint32_t) TrgProgINT->INTProg4;
    ADx->PINTS5 = (uint32_t) TrgProgINT->INTProg5;
}


/**
  * @brief  Set PMD Trigger Program Register of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  PMDTrg: The structure containing configuration for all of PMD Trigger Program Register 
  *         Refer to the members of PMD_TrgTypeDef in .h file for more detail usage. 
  * @retval None
  */
void ADC_SetPMDTrg(TSB_AD_TypeDef * ADx, const PMD_TrgTypeDef * PMDTrg)
{
    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_POINTER_NOT_NULL(PMDTrg));
    assert_param(IS_PMD_PROGx(PMDTrg->ProgNum));
    assert_param(IS_VE_PHASE(PMDTrg->Reg0_Phase));
    assert_param(IS_VE_PHASE(PMDTrg->Reg1_Phase));
    assert_param(IS_VE_PHASE(PMDTrg->Reg2_Phase));
    assert_param(IS_VE_PHASE(PMDTrg->Reg3_Phase));

    if (ADx == TSB_ADA) {
        assert_param(IS_UNIT_A_AINx(PMDTrg->Reg0_AINx));
        assert_param(IS_UNIT_A_AINx(PMDTrg->Reg1_AINx));
        assert_param(IS_UNIT_A_AINx(PMDTrg->Reg2_AINx));
        assert_param(IS_UNIT_A_AINx(PMDTrg->Reg3_AINx));

        *(ADA_PSETx_Address[PMDTrg->ProgNum]) =
            ((uint32_t) PMDTrg->Reg0_AINx | ((uint32_t) PMDTrg->Reg0_Phase << 5U)) |
            (((uint32_t) PMDTrg->Reg1_AINx | ((uint32_t) PMDTrg->Reg1_Phase << 5U)) << 8U) |
            (((uint32_t) PMDTrg->Reg2_AINx | ((uint32_t) PMDTrg->Reg2_Phase << 5U)) << 16U) |
            (((uint32_t) PMDTrg->Reg3_AINx | ((uint32_t) PMDTrg->Reg3_Phase << 5U)) << 24U);
    } else {
        assert_param(IS_UNIT_B_AINx(PMDTrg->Reg0_AINx));
        assert_param(IS_UNIT_B_AINx(PMDTrg->Reg1_AINx));
        assert_param(IS_UNIT_B_AINx(PMDTrg->Reg2_AINx));
        assert_param(IS_UNIT_B_AINx(PMDTrg->Reg3_AINx));

        *(ADB_PSETx_Address[PMDTrg->ProgNum]) =
            ((uint32_t) PMDTrg->Reg0_AINx | ((uint32_t) PMDTrg->Reg0_Phase << 5U)) |
            (((uint32_t) PMDTrg->Reg1_AINx | ((uint32_t) PMDTrg->Reg1_Phase << 5U)) << 8U) |
            (((uint32_t) PMDTrg->Reg2_AINx | ((uint32_t) PMDTrg->Reg2_Phase << 5U)) << 16U) |
            (((uint32_t) PMDTrg->Reg3_AINx | ((uint32_t) PMDTrg->Reg3_Phase << 5U)) << 24U);
    }
}


/**
  * @brief  Set Timer Trigger Program Register of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  ResultREGx: Select which ADC result register will be used for the specified ADC unit.
  *   This parameter can be one of the following values(12 registers):
  *     ADC_REG0, ADC_REG1, ADC_REG2, ADC_REG3, ADC_REG4, ADC_REG5,
  *     ADC_REG6, ADC_REG7, ADC_REG8, ADC_REG9, ADC_REG10, ADC_REG11
  * @param  MacroAINx: Select AD Channel together with its enabled or disabled setting.
  *   This parameter must be inputed with macro as the format below:
  *     TRG_ENABLE(x), TRG_DISABLE(x).
  *   'x' above can be one of the following values:
  *   for Unit A:
  *     ADC_AIN0, ADC_AIN1, ADC_AIN2, ADC_AIN3, ADC_AIN4, ADC_AIN5, ADC_AIN6,
  *     ADC_AIN7, ADC_AIN8, ADC_AIN9, ADC_AIN10, ADC_AIN11, ADC_AIN12,
  *     ADC_AIN13, ADC_AIN14
  *   for Unit B:
  *     ADC_AIN0 to ADC_AIN14 same as Unit A, ADC_AIN15, ADC_AIN16
  * @retval None
  */
void ADC_SetTimerTrg(TSB_AD_TypeDef * ADx, ADC_REGx ResultREGx, uint8_t MacroAINx)
{
    uint32_t regval = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_REGx(ResultREGx));

    if (ADx == TSB_ADA) {
        assert_param(IS_UNIT_A_AINx(MacroAINx));
    } else {
        assert_param(IS_UNIT_B_AINx(MacroAINx));
    }

    switch (ResultREGx) {
    case ADC_REG0:
    case ADC_REG1:
    case ADC_REG2:
    case ADC_REG3:
        regval = ADx->TSET03;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->TSET03 = regval;
        break;

    case ADC_REG4:
    case ADC_REG5:
    case ADC_REG6:
    case ADC_REG7:
        regval = ADx->TSET47;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->TSET47 = regval;
        break;

    case ADC_REG8:
    case ADC_REG9:
    case ADC_REG10:
    case ADC_REG11:
        regval = ADx->TSET811;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->TSET811 = regval;
        break;
    default:
        break;
    }
}


/**
  * @brief  Set Software Trigger Program Register of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  ResultREGx: Select which ADC result register will be used for the specified ADC unit.
  *   This parameter can be one of the following values(12 registers):
  *     ADC_REG0, ADC_REG1, ADC_REG2, ADC_REG3, ADC_REG4, ADC_REG5,
  *     ADC_REG6, ADC_REG7, ADC_REG8, ADC_REG9, ADC_REG10, ADC_REG11
  * @param  MacroAINx: Select AD Channel together with its enabled or disabled setting.
  *   This parameter must be inputed with macro as the format below:
  *     TRG_ENABLE(x), TRG_DISABLE(x).
  *   'x' above can be one of the following values:
  *   for Unit A:
  *     ADC_AIN0, ADC_AIN1, ADC_AIN2, ADC_AIN3, ADC_AIN4, ADC_AIN5, ADC_AIN6,
  *     ADC_AIN7, ADC_AIN8, ADC_AIN9, ADC_AIN10, ADC_AIN11, ADC_AIN12,
  *     ADC_AIN13, ADC_AIN14
  *   for Unit B:
  *     ADC_AIN0 to ADC_AIN14 same as Unit A, ADC_AIN15, ADC_AIN16
  * @retval None
  */
void ADC_SetSWTrg(TSB_AD_TypeDef * ADx, ADC_REGx ResultREGx, uint8_t MacroAINx)
{
    uint32_t regval = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_REGx(ResultREGx));

    if (ADx == TSB_ADA) {
        assert_param(IS_UNIT_A_AINx(MacroAINx));
    } else {
        assert_param(IS_UNIT_B_AINx(MacroAINx));
    }

    switch (ResultREGx) {
    case ADC_REG0:
    case ADC_REG1:
    case ADC_REG2:
    case ADC_REG3:
        regval = ADx->SSET03;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->SSET03 = regval;
        break;

    case ADC_REG4:
    case ADC_REG5:
    case ADC_REG6:
    case ADC_REG7:
        regval = ADx->SSET47;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->SSET47 = regval;
        break;

    case ADC_REG8:
    case ADC_REG9:
    case ADC_REG10:
    case ADC_REG11:
        regval = ADx->SSET811;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->SSET811 = regval;
        break;
    default:
        break;
    }
}


/**
  * @brief  Set Constant Trigger Program Register of the specified ADC unit.
  * @param  ADx: Select ADC unit
  *   This parameter can be one of the following values:
  *     TSB_ADA, TSB_ADB
  * @param  ResultREGx: Select which ADC result register will be used for the specified ADC unit.
  *   This parameter can be one of the following values(12 registers):
  *     ADC_REG0, ADC_REG1, ADC_REG2, ADC_REG3, ADC_REG4, ADC_REG5,
  *     ADC_REG6, ADC_REG7, ADC_REG8, ADC_REG9, ADC_REG10, ADC_REG11
  * @param  MacroAINx: Select AD Channel together with its enabled or disabled setting.
  *   This parameter must be inputed with macro as the format below:
  *     TRG_ENABLE(x), TRG_DISABLE(x).
  *   'x' above can be one of the following values:
  *   for Unit A:
  *     ADC_AIN0, ADC_AIN1, ADC_AIN2, ADC_AIN3, ADC_AIN4, ADC_AIN5, ADC_AIN6,
  *     ADC_AIN7, ADC_AIN8, ADC_AIN9, ADC_AIN10, ADC_AIN11, ADC_AIN12,
  *     ADC_AIN13, ADC_AIN14
  *   for Unit B:
  *     ADC_AIN0 to ADC_AIN14 same as Unit A, ADC_AIN15, ADC_AIN16
  * @retval None
  */
void ADC_SetConstantTrg(TSB_AD_TypeDef * ADx, ADC_REGx ResultREGx, uint8_t MacroAINx)
{
    uint32_t regval = 0U;

    /* Check the parameters */
    assert_param(IS_ADC_UNIT(ADx));
    assert_param(IS_ADC_REGx(ResultREGx));

    if (ADx == TSB_ADA) {
        assert_param(IS_UNIT_A_AINx(MacroAINx));
    } else {
        assert_param(IS_UNIT_B_AINx(MacroAINx));
    }

    switch (ResultREGx) {
    case ADC_REG0:
    case ADC_REG1:
    case ADC_REG2:
    case ADC_REG3:
        regval = ADx->ASET03;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->ASET03 = regval;
        break;

    case ADC_REG4:
    case ADC_REG5:
    case ADC_REG6:
    case ADC_REG7:
        regval = ADx->ASET47;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->ASET47 = regval;
        break;

    case ADC_REG8:
    case ADC_REG9:
    case ADC_REG10:
    case ADC_REG11:
        regval = ADx->ASET811;
        regval &= ~(ADC_TRG_REG_MASK << ((ResultREGx % 4U) * 8U));
        regval |= (uint32_t) MacroAINx << ((ResultREGx % 4U) * 8U);
        ADx->ASET811 = regval;
        break;
    default:
        break;
    }
}

/** @} */
/* End of group ADC_Exported_Functions */

/** @} */
/* End of group ADC */

/** @} */
/* End of group TX03_Periph_Driver */

#endif                          /* defined(__TMPM370_ADC_H) */
