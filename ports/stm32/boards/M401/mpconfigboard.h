#define MICROPY_HW_BOARD_NAME       "F401-core"
#define MICROPY_HW_MCU_NAME         "STM32F401CCU6"

#define MICROPY_EMIT_THUMB          (0)
#define MICROPY_EMIT_INLINE_THUMB   (0)
#define MICROPY_PY_BUILTINS_COMPLEX (0)
#define MICROPY_PY_USOCKET          (0)
#define MICROPY_PY_NETWORK          (0)

#define MICROPY_HW_HAS_SWITCH       (1)
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SERVO     (0)

#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)

// block device config for SPI flash
#if !MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE
// use external SPI flash for storage
#define MICROPY_HW_SPIFLASH_SIZE_BITS (64 * 1024 * 1024)
#define MICROPY_HW_SPIFLASH_INDEX (&spi_obj[1])
#define MICROPY_HW_SPIFLASH_CS      (pin_B12)
#define MICROPY_HW_SPIFLASH_SCK     (pin_B13)
#define MICROPY_HW_SPIFLASH_MOSI    (pin_B15)
#define MICROPY_HW_SPIFLASH_MISO    (pin_B14)

extern const struct _mp_spiflash_config_t spiflash_config;
extern struct _spi_bdev_t spi_bdev;
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? (MICROPY_HW_SPIFLASH_SIZE_BITS / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&spiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#define MICROPY_HW_BDEV_READBLOCKS(dest, bl, n) spi_bdev_readblocks(&spi_bdev, (dest), (bl), (n))
#define MICROPY_HW_BDEV_WRITEBLOCKS(src, bl, n) spi_bdev_writeblocks(&spi_bdev, (src), (bl), (n))
#endif

#define MICROPY_DFU_MODE (0)
#define MICROPY_PY_THREAD (0)
#define MICROPY_HW_ENABLE_ADC (1)
#define CONFIG_REFRESH_PYBCDC (0)
#define CONFIG_FRESH_README (0)

// Pico has an 8 MHz HSE and the F401 does 84 MHz max
#define MICROPY_HW_CLK_HSI (1)
#define MICROPY_HW_CLK_LSI (0)
#if MICROPY_HW_CLK_HSI
#define MICROPY_HW_CLK_PLLM (8) // (10)
#else
#define MICROPY_HW_CLK_PLLM (5) // (5)
#endif
#define MICROPY_HW_CLK_PLLN (216)
#define MICROPY_HW_CLK_PLLP (RCC_PLLP_DIV4)
#define MICROPY_HW_CLK_PLLQ (9) // (7)

// does not have a 32kHz crystal
#define MICROPY_HW_RTC_USE_LSE      (0)

// UART config
#define MICROPY_HW_UART1_TX     (pin_B6)
#define MICROPY_HW_UART1_RX     (pin_B7)
#define MICROPY_HW_UART2_TX     (pin_A2)
#define MICROPY_HW_UART2_RX     (pin_A3)
#define MICROPY_HW_UART2_RTS    (pin_A1)
#define MICROPY_HW_UART2_CTS    (pin_A0)
#define MICROPY_HW_UART6_TX     (pin_A11)
#define MICROPY_HW_UART6_RX     (pin_A12)

// I2C busses
#if 0
#define MICROPY_HW_I2C1_SCL (pin_B6)
#define MICROPY_HW_I2C1_SDA (pin_B7)
#define MICROPY_HW_I2C2_SCL (pin_B10)
#define MICROPY_HW_I2C2_SDA (pin_B3)
#define MICROPY_HW_I2C3_SCL (pin_A8)
#define MICROPY_HW_I2C3_SDA (pin_B4)
#endif

// SPI busses
#define MICROPY_HW_SPI1_NSS  (pin_A4)
#define MICROPY_HW_SPI1_SCK  (pin_A5)
#define MICROPY_HW_SPI1_MISO (pin_A6)
#define MICROPY_HW_SPI1_MOSI (pin_A7)
#if 0
#define MICROPY_HW_SPI2_NSS  (pin_B12)
#define MICROPY_HW_SPI2_SCK  (pin_B13)
#define MICROPY_HW_SPI2_MISO (pin_B14)
#define MICROPY_HW_SPI2_MOSI (pin_B15)
#endif
// BTN1 has no pullup or pulldown; it is active high and broken out on a header
#define MICROPY_HW_USRSW_PIN        (pin_A15)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLDOWN)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_RISING)
#define MICROPY_HW_USRSW_PRESSED    (1)

// Pico has 2 LEDs
#define MICROPY_HW_LED1             (pin_C13)  // red
#define MICROPY_HW_LED2             (pin_C14) // green
#define MICROPY_HW_LED3             (pin_C15) // green
#define MICROPY_HW_LED4             (pin_H0) // green
#define MICROPY_HW_LED_OFF(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_ON(pin)     (mp_hal_pin_low(pin))

// USB config
#define MICROPY_HW_USB_FS (1)
#define MICROPY_HW_USB_VBUS_DETECT_PIN (pin_A9)
#define MICROPY_HW_USB_OTG_ID_PIN      (pin_A10)

