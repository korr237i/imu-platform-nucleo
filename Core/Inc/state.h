/*
 * state.h
 *
 *  Created on: 11 нояб. 2017 г.
 *      Author: Korr237i
 *
 *  This header included main structure to share data from module to module
 */

#ifndef STATE_H_
#define STATE_H_

#include <stdint.h>
#include <stdbool.h>

#include <stm32f3xx_hal.h>

#include "lsm/lsm6ds3_reg.h"
#include "lsm/lis3mdl_reg.h"

#include "quaternion.h"

#define MPU9255			0
#define LSM6DS3			1
#define LSM303C			1
#define IMU_CALIBRATION	0

//--------- LSM6DS3 ---------------
#define LSM6DS3_PORT		GPIOA
#define LSM6DS3_CS_PIN		GPIO_PIN_12
#define LSM6DS3_SCK_PIN		GPIO_PIN_13
#define LSM6DS3_MISO_PIN	GPIO_PIN_14
#define LSM6DS3_MOSI_PIN	GPIO_PIN_15


// if error set value and go to end
#define PROCESS_ERROR(x) if (0 != (error = (x))) { goto end; }


/*#################################################*/
/*################## СТРУКТУРЫ ###################*/
/*#################################################*/

/*
 * 	Структуры состояний аппарата
 */
typedef struct {
	//GPS data
	float coordinates[2];
	float speed;
	float course;
	float time;
} stateGPS_t;


//	IMU data in RSC (related system of coordinates)
typedef struct {
	float accel[3];
	float gyro[3];
	float magn[3];
} stateIMU_rsc_t;


//	orientation and position of device in ISC (inertial system of coordinates)
typedef struct {
	//	IMU data
	float accel[3];
	float magn[3];

	//	position
	float velocities[3];
	float coordinates[3];

	//	orientation
	float quaternion[4];
} stateIMU_isc_t;

//	system parameters
typedef struct {
	uint8_t MPU_state;		//	state of MPU9255
	uint8_t SD_state;		//	state of SD
	uint8_t NRF_state;		//	state of NRF24L01
	uint8_t GPS_state;		//	state of GPS-module

	float time;				//	current time
	float magnASA[3];
} state_system_t;


typedef struct {
	//	zero params; this fields should be filled when device started it`s work
	double zero_pressure;
	float zero_quaternion[4];
	float zero_GPS[2];
	float gyro_staticShift[3];
	float accel_staticShift[3];
} state_zero_t;


/*##################################################*/
/*################### ПЕРЕМЕННЫЕ ###################*/
/*##################################################*/

extern UART_HandleTypeDef	huart1;
extern I2C_HandleTypeDef 	hi2c1;

extern lsm6ds3_ctx_t lsm6ds3_dev_ctx;
extern lis3mdl_ctx_t lsm303c_dev_ctx;

// глобальные структуры
extern stateGPS_t 			stateGPS;
extern stateIMU_rsc_t 		stateIMU_rsc;
extern stateIMU_isc_t 		stateIMU_isc;
extern state_system_t 		state_system;
extern state_zero_t			state_zero;

extern stateIMU_isc_t		stateIMU_isc_prev;
extern state_system_t		state_system_prev;


#endif /* STATE_H_ */
