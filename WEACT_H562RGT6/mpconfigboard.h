#define MICROPY_HW_BOARD_NAME       "WeAct STM32H562RGT6"
#define MICROPY_HW_MCU_NAME         "STM32H562RGT6"

#define MICROPY_PY_PYB_LEGACY               (0)
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (1)
#define MICROPY_HW_ENABLE_RTC               (1)
#define MICROPY_HW_ENABLE_RNG               (1)
#define MICROPY_HW_ENABLE_ADC               (1)
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

// UART config (change if your board uses different pins for UART1)
#define MICROPY_HW_UART1_TX                 (pin_A9)
#define MICROPY_HW_UART1_RX                 (pin_A10)
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
