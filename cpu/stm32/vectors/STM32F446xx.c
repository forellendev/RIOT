
/*
 * PLEASE DON'T EDIT
 *
 * This file was automatically generated by
 * ./cpu/stm32/dist/irqs/gen_vectors.py
 */

#include "vectors_cortexm.h"

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void) {
    dummy_handler_default();
}

/* STM32F446xx specific interrupt vectors */
WEAK_DEFAULT void isr_wwdg(void);
WEAK_DEFAULT void isr_pvd(void);
WEAK_DEFAULT void isr_tamp_stamp(void);
WEAK_DEFAULT void isr_rtc_wkup(void);
WEAK_DEFAULT void isr_flash(void);
WEAK_DEFAULT void isr_rcc(void);
WEAK_DEFAULT void isr_exti(void);
WEAK_DEFAULT void isr_dma1_stream0(void);
WEAK_DEFAULT void isr_dma1_stream1(void);
WEAK_DEFAULT void isr_dma1_stream2(void);
WEAK_DEFAULT void isr_dma1_stream3(void);
WEAK_DEFAULT void isr_dma1_stream4(void);
WEAK_DEFAULT void isr_dma1_stream5(void);
WEAK_DEFAULT void isr_dma1_stream6(void);
WEAK_DEFAULT void isr_adc(void);
WEAK_DEFAULT void isr_can1_tx(void);
WEAK_DEFAULT void isr_can1_rx0(void);
WEAK_DEFAULT void isr_can1_rx1(void);
WEAK_DEFAULT void isr_can1_sce(void);
WEAK_DEFAULT void isr_tim1_brk_tim9(void);
WEAK_DEFAULT void isr_tim1_up_tim10(void);
WEAK_DEFAULT void isr_tim1_trg_com_tim11(void);
WEAK_DEFAULT void isr_tim1_cc(void);
WEAK_DEFAULT void isr_tim2(void);
WEAK_DEFAULT void isr_tim3(void);
WEAK_DEFAULT void isr_tim4(void);
WEAK_DEFAULT void isr_i2c1_ev(void);
WEAK_DEFAULT void isr_i2c1_er(void);
WEAK_DEFAULT void isr_i2c2_ev(void);
WEAK_DEFAULT void isr_i2c2_er(void);
WEAK_DEFAULT void isr_spi1(void);
WEAK_DEFAULT void isr_spi2(void);
WEAK_DEFAULT void isr_usart1(void);
WEAK_DEFAULT void isr_usart2(void);
WEAK_DEFAULT void isr_usart3(void);
WEAK_DEFAULT void isr_rtc_alarm(void);
WEAK_DEFAULT void isr_otg_fs_wkup(void);
WEAK_DEFAULT void isr_tim8_brk_tim12(void);
WEAK_DEFAULT void isr_tim8_up_tim13(void);
WEAK_DEFAULT void isr_tim8_trg_com_tim14(void);
WEAK_DEFAULT void isr_tim8_cc(void);
WEAK_DEFAULT void isr_dma1_stream7(void);
WEAK_DEFAULT void isr_fmc(void);
WEAK_DEFAULT void isr_sdio(void);
WEAK_DEFAULT void isr_tim5(void);
WEAK_DEFAULT void isr_spi3(void);
WEAK_DEFAULT void isr_uart4(void);
WEAK_DEFAULT void isr_uart5(void);
WEAK_DEFAULT void isr_tim6_dac(void);
WEAK_DEFAULT void isr_tim7(void);
WEAK_DEFAULT void isr_dma2_stream0(void);
WEAK_DEFAULT void isr_dma2_stream1(void);
WEAK_DEFAULT void isr_dma2_stream2(void);
WEAK_DEFAULT void isr_dma2_stream3(void);
WEAK_DEFAULT void isr_dma2_stream4(void);
WEAK_DEFAULT void isr_can2_tx(void);
WEAK_DEFAULT void isr_can2_rx0(void);
WEAK_DEFAULT void isr_can2_rx1(void);
WEAK_DEFAULT void isr_can2_sce(void);
WEAK_DEFAULT void isr_otg_fs(void);
WEAK_DEFAULT void isr_dma2_stream5(void);
WEAK_DEFAULT void isr_dma2_stream6(void);
WEAK_DEFAULT void isr_dma2_stream7(void);
WEAK_DEFAULT void isr_usart6(void);
WEAK_DEFAULT void isr_i2c3_ev(void);
WEAK_DEFAULT void isr_i2c3_er(void);
WEAK_DEFAULT void isr_otg_hs_ep1_out(void);
WEAK_DEFAULT void isr_otg_hs_ep1_in(void);
WEAK_DEFAULT void isr_otg_hs_wkup(void);
WEAK_DEFAULT void isr_otg_hs(void);
WEAK_DEFAULT void isr_dcmi(void);
WEAK_DEFAULT void isr_fpu(void);
WEAK_DEFAULT void isr_spi4(void);
WEAK_DEFAULT void isr_sai1(void);
WEAK_DEFAULT void isr_sai2(void);
WEAK_DEFAULT void isr_quadspi(void);
WEAK_DEFAULT void isr_cec(void);
WEAK_DEFAULT void isr_spdif_rx(void);
WEAK_DEFAULT void isr_fmpi2c1_ev(void);
WEAK_DEFAULT void isr_fmpi2c1_er(void);

/* CPU specific interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    [WWDG_IRQn                          ] = isr_wwdg,
    [PVD_IRQn                           ] = isr_pvd,
    [TAMP_STAMP_IRQn                    ] = isr_tamp_stamp,
    [RTC_WKUP_IRQn                      ] = isr_rtc_wkup,
    [FLASH_IRQn                         ] = isr_flash,
    [RCC_IRQn                           ] = isr_rcc,
    [EXTI0_IRQn                         ] = isr_exti,
    [EXTI1_IRQn                         ] = isr_exti,
    [EXTI2_IRQn                         ] = isr_exti,
    [EXTI3_IRQn                         ] = isr_exti,
    [EXTI4_IRQn                         ] = isr_exti,
    [DMA1_Stream0_IRQn                  ] = isr_dma1_stream0,
    [DMA1_Stream1_IRQn                  ] = isr_dma1_stream1,
    [DMA1_Stream2_IRQn                  ] = isr_dma1_stream2,
    [DMA1_Stream3_IRQn                  ] = isr_dma1_stream3,
    [DMA1_Stream4_IRQn                  ] = isr_dma1_stream4,
    [DMA1_Stream5_IRQn                  ] = isr_dma1_stream5,
    [DMA1_Stream6_IRQn                  ] = isr_dma1_stream6,
    [ADC_IRQn                           ] = isr_adc,
    [CAN1_TX_IRQn                       ] = isr_can1_tx,
    [CAN1_RX0_IRQn                      ] = isr_can1_rx0,
    [CAN1_RX1_IRQn                      ] = isr_can1_rx1,
    [CAN1_SCE_IRQn                      ] = isr_can1_sce,
    [EXTI9_5_IRQn                       ] = isr_exti,
    [TIM1_BRK_TIM9_IRQn                 ] = isr_tim1_brk_tim9,
    [TIM1_UP_TIM10_IRQn                 ] = isr_tim1_up_tim10,
    [TIM1_TRG_COM_TIM11_IRQn            ] = isr_tim1_trg_com_tim11,
    [TIM1_CC_IRQn                       ] = isr_tim1_cc,
    [TIM2_IRQn                          ] = isr_tim2,
    [TIM3_IRQn                          ] = isr_tim3,
    [TIM4_IRQn                          ] = isr_tim4,
    [I2C1_EV_IRQn                       ] = isr_i2c1_ev,
    [I2C1_ER_IRQn                       ] = isr_i2c1_er,
    [I2C2_EV_IRQn                       ] = isr_i2c2_ev,
    [I2C2_ER_IRQn                       ] = isr_i2c2_er,
    [SPI1_IRQn                          ] = isr_spi1,
    [SPI2_IRQn                          ] = isr_spi2,
    [USART1_IRQn                        ] = isr_usart1,
    [USART2_IRQn                        ] = isr_usart2,
    [USART3_IRQn                        ] = isr_usart3,
    [EXTI15_10_IRQn                     ] = isr_exti,
    [RTC_Alarm_IRQn                     ] = isr_rtc_alarm,
    [OTG_FS_WKUP_IRQn                   ] = isr_otg_fs_wkup,
    [TIM8_BRK_TIM12_IRQn                ] = isr_tim8_brk_tim12,
    [TIM8_UP_TIM13_IRQn                 ] = isr_tim8_up_tim13,
    [TIM8_TRG_COM_TIM14_IRQn            ] = isr_tim8_trg_com_tim14,
    [TIM8_CC_IRQn                       ] = isr_tim8_cc,
    [DMA1_Stream7_IRQn                  ] = isr_dma1_stream7,
    [FMC_IRQn                           ] = isr_fmc,
    [SDIO_IRQn                          ] = isr_sdio,
    [TIM5_IRQn                          ] = isr_tim5,
    [SPI3_IRQn                          ] = isr_spi3,
    [UART4_IRQn                         ] = isr_uart4,
    [UART5_IRQn                         ] = isr_uart5,
    [TIM6_DAC_IRQn                      ] = isr_tim6_dac,
    [TIM7_IRQn                          ] = isr_tim7,
    [DMA2_Stream0_IRQn                  ] = isr_dma2_stream0,
    [DMA2_Stream1_IRQn                  ] = isr_dma2_stream1,
    [DMA2_Stream2_IRQn                  ] = isr_dma2_stream2,
    [DMA2_Stream3_IRQn                  ] = isr_dma2_stream3,
    [DMA2_Stream4_IRQn                  ] = isr_dma2_stream4,
    [CAN2_TX_IRQn                       ] = isr_can2_tx,
    [CAN2_RX0_IRQn                      ] = isr_can2_rx0,
    [CAN2_RX1_IRQn                      ] = isr_can2_rx1,
    [CAN2_SCE_IRQn                      ] = isr_can2_sce,
    [OTG_FS_IRQn                        ] = isr_otg_fs,
    [DMA2_Stream5_IRQn                  ] = isr_dma2_stream5,
    [DMA2_Stream6_IRQn                  ] = isr_dma2_stream6,
    [DMA2_Stream7_IRQn                  ] = isr_dma2_stream7,
    [USART6_IRQn                        ] = isr_usart6,
    [I2C3_EV_IRQn                       ] = isr_i2c3_ev,
    [I2C3_ER_IRQn                       ] = isr_i2c3_er,
    [OTG_HS_EP1_OUT_IRQn                ] = isr_otg_hs_ep1_out,
    [OTG_HS_EP1_IN_IRQn                 ] = isr_otg_hs_ep1_in,
    [OTG_HS_WKUP_IRQn                   ] = isr_otg_hs_wkup,
    [OTG_HS_IRQn                        ] = isr_otg_hs,
    [DCMI_IRQn                          ] = isr_dcmi,
    [FPU_IRQn                           ] = isr_fpu,
    [SPI4_IRQn                          ] = isr_spi4,
    [SAI1_IRQn                          ] = isr_sai1,
    [SAI2_IRQn                          ] = isr_sai2,
    [QUADSPI_IRQn                       ] = isr_quadspi,
    [CEC_IRQn                           ] = isr_cec,
    [SPDIF_RX_IRQn                      ] = isr_spdif_rx,
    [FMPI2C1_EV_IRQn                    ] = isr_fmpi2c1_ev,
    [FMPI2C1_ER_IRQn                    ] = isr_fmpi2c1_er,
};
