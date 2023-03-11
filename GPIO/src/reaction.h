#ifndef __REACTION_H__
#define __REACTION_H__


//-------------------
// RCC configuration
//-------------------

void board_clocking_init(void) {

    // (1) Clock HSE and wait for oscillations to setup.
    REG_RCC_CR_CLOCK_HSE_ON(REG_RCC_CR);
    WHILE_STATE_ESTABLISHMENT(REG_RCC_CR, REG_RCC_CR_STAB);

    // (2) Configure PLL:
    // PREDIV output: HSE/2 = 4 MHz
    REG_RCC_CFGR2_CONFIGURATE_PLL(REG_RCC_CFGR2, 2U);

    // (3) Select PREDIV output as PLL input (4 MHz):
    REG_RCC_CFGR_SELECT_PLL_DIV(REG_RCC_CFGR, HSI_SRC);

    // (4) Set PLLMUL to 12:
    // SYSCLK frequency = 48 MHz
    REG_RCC_CFGR_SELECT_PLL_MUL(REG_RCC_CFGR, 12);

    // (5) Enable PLL:
    REG_RCC_CR_ENABLE_PLL(REG_RCC_CR);
    //WHILE_STATE_ESTABLISHMENT(REG_RCC_CR, REG_RCC_CR_STAB1);

    // (6) Configure AHB frequency to 48 MHz:
    REG_RCC_CFGR_CONFIGURATE_AHB(REG_RCC_CFGR, 0);

    // (7) Select PLL as SYSCLK source:
    REG_RCC_CFGR_SELECT_PLL_SYSCLK(REG_RCC_CFGR, AHB_TO_PLL);
    //WHILE_STATE_ESTABLISHMENT(REG_RCC_CFGR, REG_RCC_CFGR_STAB1);

    // (8) Set APB frequency to 24 MHz
    REG_RCC_CFGR_SET_APB_FREQ(REG_RCC_CFGR);
}


//--------------------
// GPIO configuration
//--------------------

void board_gpio_init(void) {

    // (1) Configure PA1-PA12 as output:
    REG_RCC_AHBENR_CONFIGURATE_PA1_PA12_OUTPUT(REG_RCC_AHBENR, REG_RCC_AHBENR_PA1_PA12_OUTPUT_VALUE);

    // Configure mode register:
    GPIOA_MODER_SET(GPIOA_MODER, GPIOA_CONFIGURATE_MODE_VALUE);

    // Configure type register:
    GPIOA_TYPER_SET(GPIOA_TYPER, 0U);

    // (2) Configure PA0 as button:
    GPIOA_MODER_CONFIGURATE_PA0_BUTTON(GPIOA_MODER, 0U);

    // Configure PA0 as pull-down pin:
    GPIOA_PUPDR_CONFIGURATE_PA0_MODE(GPIOA_PUPDR, PULL_DOWN);
}


void to_get_more_accuracy_pay(void) {
    
    for(uint32_t i = 0; i < ONE_MILLISECOND / 3U; ++i) {

        // Insert NOP for power consumption:
        __asm__ volatile("nop");
    }
}

#endif