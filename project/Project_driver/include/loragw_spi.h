#ifndef LORAGW_SPI
#define LORAGW_SPI

#define LGW_SPI_SUCCESS     0
#define LGW_SPI_ERROR       -1
#define LGW_BURST_CHUNK     1024

#define LGW_SPI_MUX_MODE0   0x0     /* No FPGA */
#define LGW_SPI_MUX_MODE1   0x1     /* FPGA, with spi mux header */

#define LGW_SPI_MUX_TARGET_SX1301   0x0
#define LGW_SPI_MUX_TARGET_FPGA     0x1
#define LGW_SPI_MUX_TARGET_EEPROM   0x2
#define LGW_SPI_MUX_TARGET_SX127X   0x3

int lgw_spi_open(void **spi_target_ptr);
int lgw_spi_close(void *spi_target);
int lgw_spi_w(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t data);
int lgw_spi_r(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t *data);
int lgw_spi_wb(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t *data, uint16_t size);
int lgw_spi_rb(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t *data, uint16_t size);
    
#endif