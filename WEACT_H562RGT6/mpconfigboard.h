
#define MICROPY_HW_BOARD_NAME       "WeAct STM32H562RGT6"
#define MICROPY_HW_MCU_NAME         "STM32H562RGT6"

#define MICROPY_PY_PYB_LEGACY               (0)
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)
#define MICROPY_HW_ENABLE_RTC               (1)
#define MICROPY_HW_ENABLE_RNG               (1)
#define MICROPY_HW_ENABLE_ADC               (0)  // no ADC support
#define MICROPY_HW_ENABLE_DAC               (1)
#define MICROPY_HW_ENABLE_USB               (1)
#define MICROPY_HW_HAS_SWITCH               (0)
#define MICROPY_HW_HAS_FLASH                (1)

// The board has an 8MHz crystal
#define MICROPY_HW_CLK_USE_BYPASS           (0)
#define MICROPY_HW_CLK_PLLM                 (2)
#define MICROPY_HW_CLK_PLLN                 (125)
#define MICROPY_HW_CLK_PLLP                 (2)
#define MICROPY_HW_CLK_PLLQ                 (2)
#define MICROPY_HW_CLK_PLLR                 (2)
#define MICROPY_HW_CLK_PLLVCI_LL            (LL_RCC_PLLINPUTRANGE_4_8)
#define MICROPY_HW_CLK_PLLVCO_LL            (LL_RCC_PLLVCORANGE_WIDE)
#define MICROPY_HW_CLK_PLLFRAC              (0)

// PLL3 with Q output at 48MHz for USB
#define MICROPY_HW_CLK_PLL3M                (8)
#define MICROPY_HW_CLK_PLL3N                (192)
#define MICROPY_HW_CLK_PLL3P                (2)
#define MICROPY_HW_CLK_PLL3Q                (4)
#define MICROPY_HW_CLK_PLL3R                (2)
#define MICROPY_HW_CLK_PLL3FRAC             (0)
#define MICROPY_HW_CLK_PLL3VCI_LL           (LL_RCC_PLLINPUTRANGE_1_2)
#define MICROPY_HW_CLK_PLL3VCO_LL           (LL_RCC_PLLVCORANGE_MEDIUM)

#define MICROPY_HW_FLASH_LATENCY            FLASH_LATENCY_5

#define MICROPY_HW_RTC_USE_LSE              (1)


// UART config (change if your board uses different pins for UART1, which has 'pin_A9', 'pin_A10' as working values)
#define MICROPY_HW_UART1_TX                 (pyb_pin_UART1_TX)
#define MICROPY_HW_UART1_RX                 (pyb_pin_UART1_RX)
#define MICROPY_HW_UART2_TX                 (pyb_pin_UART2_TX)
#define MICROPY_HW_UART2_RX                 (pyb_pin_UART2_RX)
#define MICROPY_HW_UART3_TX                 (pyb_pin_UART3_TX)
#define MICROPY_HW_UART3_RX                 (pyb_pin_UART3_RX)
// UART4 removed to avoid SD card conflict
// #define MICROPY_HW_UART4_TX              (pyb_pin_UART4_TX)
// #define MICROPY_HW_UART4_RX              (pyb_pin_UART4_RX)
#define MICROPY_HW_UART_REPL                PYB_UART_1
#define MICROPY_HW_UART_REPL_BAUD           115200

// I2C config (default to PB6/PB7, adjust if needed)
#define MICROPY_HW_I2C1_SCL                 (pin_B6)
#define MICROPY_HW_I2C1_SDA                 (pin_B7)

// SPI config (default to PA4/PA5/PA6/PA7, adjust if needed)
#define MICROPY_HW_SPI1_NSS                 (pin_A4)
#define MICROPY_HW_SPI1_SCK                 (pin_A5)
#define MICROPY_HW_SPI1_MISO                (pin_A6)
#define MICROPY_HW_SPI1_MOSI                (pin_A7)

// LED config
#define MICROPY_HW_LED1                     (pin_B2)
#define MICROPY_HW_LED_ON(pin)              (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)             (mp_hal_pin_low(pin))

// USB config (FS on PA11/PA12 is typical)
#define MICROPY_HW_USB_FS                   (1)

// === SD card (SDMMC/SDIO) support ===
#define MICROPY_HW_ENABLE_SDCARD            (1)
// No card detect pin defined, as socket does not provide one
// #define MICROPY_HW_SDCARD_DETECT_PIN        (pin_Xx)
// #define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
// #define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_RESET)
// SDMMC pins are configured via pins.csv:
// SD_D0  PC8
// SD_D1  PC9
// SD_D2  PC10
// SD_D3  PC11
// SD_CMD PD2
// SD_CK  PC12

/* --- SDMMC1 AF PATCH BEGIN --- */
// SDMMC1 AF defines (patch inserted by build-weactstmh562.sh)
#ifndef STATIC_AF_SDMMC1_CK
#define STATIC_AF_SDMMC1_CK(x)  (12)
#endif
#ifndef STATIC_AF_SDMMC1_CMD
#define STATIC_AF_SDMMC1_CMD(x) (12)
#endif
#ifndef STATIC_AF_SDMMC1_D0
#define STATIC_AF_SDMMC1_D0(x)  (12)
#endif
#ifndef STATIC_AF_SDMMC1_D1
#define STATIC_AF_SDMMC1_D1(x)  (12)
#endif
#ifndef STATIC_AF_SDMMC1_D2
#define STATIC_AF_SDMMC1_D2(x)  (12)
#endif
#ifndef STATIC_AF_SDMMC1_D3
#define STATIC_AF_SDMMC1_D3(x)  (12)
#endif
/* --- SDMMC1 AF PATCH END --- */
