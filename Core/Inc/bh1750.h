/*
 * bh1750.h
 *
 *  Created on: Aug 8, 2025
 *      Author: Admin
 */

#ifndef INC_BH1750_H_
#define INC_BH1750_H_

//Device Address
//Please note that arduino uses 7 bit addresses, STM32 uses 8
#define BH1750_NO_GROUND_ADDR_WRITE     (0xB9 + 0)
#define BH1750_NO_GROUND_ADDR_READ      (0xB9 + 1)
#define BH1750_GROUND_ADDR_WRITE        (0x46 + 0)
#define BH1750_GROUND_ADDR_READ     (0x46 + 1)


#define CMD_POWER_DOWN          0x00
#define CMD_POWER_ON            0x01
#define CMD_RESET               0x03
#define CMD_H_RES_MODE          0x10
#define CMD_H_RES_MODE2         0x11
#define CMD_L_RES_MODE          0x13
#define CMD_ONE_H_RES_MODE      0x20
#define CMD_ONE_H_RES_MODE2     0x21
#define CMD_ONE_L_RES_MODE      0x23
#define CMD_CNG_TIME_HIGH       0x30    // 3 LSB set time
#define CMD_CNG_TIME_LOW        0x60    // 5 LSB set time



typedef struct BH1750_device BH1750_device_t;

struct BH1750_device{
    uint8_t address_r;
    uint8_t address_w;

    uint16_t value;

    uint8_t buffer[2];

    uint8_t mode;

    uint8_t (*lux_sensor_init)(BH1750_device_t *BH1750_device);
    uint8_t (*read_lux_sensor)(BH1750_device_t *BH1750_device);
    uint8_t (*write_cmd_to_lux_sensor)(BH1750_device_t *BH1750_device, uint8_t cmd);
    uint8_t (*data_handler)(BH1750_device_t *BH1750_device);
} ;


BH1750_device_t *bh1750_sensor_init(void);



#endif /* INC_BH1750_H_ */
