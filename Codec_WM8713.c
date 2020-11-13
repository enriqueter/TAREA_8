/*
 * Codec_WM8713.c
 *
 *  Created on: 13 nov. 2020
 *      Author: etera
 */

#include "Codec_WM8713.h"
#include "FreeRTOS.h"
#include "task.h"
#include "MK66F18.h"

#define I2C_SCL		2U
#define I2C_SDA		3U
#define BAUD_RATE	100000
#define I2C_DELAY	100//(ms)

/*Global declaratios*/
static freertos_i2c_config_t WM8731_i2c_config;

freertos_i2c_flag_t WN8731_init(void)
{
	freertos_i2c_flag_t WM8731_sucess = freertos_i2c_fail;
	/*Start port and freertos i2c inicialization */
	WM8731_i2c_config.baudrate = BAUD_RATE;
	WM8731_i2c_config.i2c_number = 	freertos_i2c0;
	WM8731_i2c_config.port = freertos_i2c_portB;
	WM8731_i2c_config.scl_pin = I2C_SCL;
	WM8731_i2c_config.sda_pin = I2C_SDA;
	WM8731_i2c_config.pin_mux = kPORT_MuxAlt2;

	/*Init configuration for freertos i2c*/
	WM8731_sucess = freertos_i2c_init(WM8731_i2c_config);

	vTaskDelay(pdMS_TO_TICKS(10));

	/*If i2c configuration succeed */
	if(freertos_i2c_sucess == WM8731_sucess)
	{

		/*reset configuration to fail*/
		WM8731_sucess = freertos_i2c_fail;

		/*Send  configuration of WM87311*/

		/*Write PowerON Register*/
		uint8_t data[2] = {WM8731_POWER_DOWN_REGISTER, 0x00};
		WM8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		/*Write Left Line In Register*/
		data[0] = WM8731_LEFT_LINE_IN;
		data[1] = 23;
		WM8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		/*Write Right Line In Register*/
		data[0] = WM8731_RIGHT_LINE_IN;
		data[1] = 23;
		WM8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		/*Write Analogue audio Path  Register*/
		data[0] = WM8731_ANALOGUE_AUDIO;
		data[1] = 0x05;
		WM8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));

		/*Write Codec Enable  Register*/
		data[0] = WM8731_CODEC_ENABLE;
		data[1] = 0x01;
		WM8731_sucess = freertos_i2c_transmit(WM8731_i2c_config.i2c_number, data , 2, WM8731_SLAVE_ADDRESS);
		vTaskDelay(pdMS_TO_TICKS(I2C_DELAY));


	}
	/*Task succeed flag*/
	return WM8731_sucess;
}

