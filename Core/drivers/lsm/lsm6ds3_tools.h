#ifndef DRIVERS_LSM_LSM6DS3_TOOLS_H_
#define DRIVERS_LSM_LSM6DS3_TOOLS_H_

#include <stdint.h>

extern I2C_HandleTypeDef* i2c_lsm6ds3;

int32_t lsm6ds3_platform_init(void);

uint32_t lsm6ds3_get_xl_data_g(float* accel);
uint32_t lsm6ds3_get_g_data_rps(float* gyro);

#endif /* DRIVERS_LSM_LSM6DS3_TOOLS_H_ */
