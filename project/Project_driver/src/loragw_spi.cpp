
#include <stdint.h>        /* C99 types */
#include <stdio.h>        /* printf fprintf */
//#include <stdlib.h>        /* malloc free */
//#include <unistd.h>        /* lseek, close */
//#include <fcntl.h>        /* open */
//#include <string.h>        /* memset */
#include <mbed.h>
#define WRITE_ACCESS 0x80
#define READ_ACCESS 0x00
SPI spi(D11, D12, D13);
DigitalOut cs(D10);
//#include "loragw_spi.h"
//#include "loragw_hal.h"


int lgw_spi_open(void **spi_target_ptr) {
	cs = 1;
    spi.format(8,3);
    spi.frequency(1000000);
    cs = 0;
	return 0;//compat
}
int lgw_spi_close(void *spi_target){
	return 0;//compat
	} 
/* simple write | only argument used is data */
int lgw_spi_w(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t data) {
	uint8_t receivedata = 0;
	uint8_t command;
	command = WRITE_ACCESS | (address & 0x7F);
	cs = 0;
	spi.write(command);
	receivedata = spi.write(data); // write data to be transmitted to the SPI data register
	printf("datawrite: %d", receivedata);
	cs = 1;
	return 0;//compat
}

int lgw_spi_r(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t *data) {
	uint8_t command;
	command = READ_ACCESS | (address & 0x7F);
	cs = 0;
	spi.write(command);
	*data = 5;
	*data = spi.write(0x00);
	printf("dataread: %d", *data);
	cs = 1;
	return 0;//compat
}

int lgw_spi_wb(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t *data, uint16_t size) {
	uint32_t chunk_size, offset;
	uint32_t size_to_do = size;
	uint16_t i = 0;
	uint8_t LGW_BURST_CHUNK = sizeof(uint8_t);
	uint8_t command;
	/*super ghetto write burst function*/
	/* mux mode and targets can be safely ignored*/
	
	command = WRITE_ACCESS | (address & 0x7F);
	cs = 0;
	spi.write(command); //set target register (i hope)
	printf("here too\n");
	for (i = 0; size_to_do > 0; i++) {
        chunk_size = (size_to_do < LGW_BURST_CHUNK) ? size_to_do : LGW_BURST_CHUNK;
        offset = i * LGW_BURST_CHUNK;
        printf("sending %d", *(data + offset));
        spi.write(*(data + offset));
        size_to_do -= chunk_size; /* subtract the quantity of data already transferred */
    }
    cs = 1;
    return 0;//compat
}

/* Burst (multiple-byte) read */
/*first three arguments are safe to NULL out */
int lgw_spi_rb(void *spi_target, uint8_t spi_mux_mode, uint8_t spi_mux_target, uint8_t address, uint8_t *data, uint16_t size) {
	uint32_t chunk_size, offset;
	uint32_t size_to_do = size;
	uint16_t i = 0;
	uint8_t LGW_BURST_CHUNK = sizeof(uint8_t);
	uint8_t command;
	
	command = READ_ACCESS | (address & 0x7F);
	cs = 0;
	spi.write(command);
	
	for(i = 0; size_to_do > 0; i++){//read loop
		chunk_size = (size_to_do < LGW_BURST_CHUNK) ? size_to_do : LGW_BURST_CHUNK;
		offset = i + LGW_BURST_CHUNK;
		*(data + offset) = spi.write(0x00);
		printf("received %d\n", *(data + offset));
		size_to_do -= chunk_size;
	}
	cs = 1;
	return 0;//compat
}