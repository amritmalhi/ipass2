#ifndef MPU6050_HPP
#define MPU6050_HPP

#include "hwlib.hpp"

class mpu6050 {
private:
	hwlib::i2c_bus_bit_banged_scl_sda mpu;

	const uint8_t PWR_MGMT_1 = 0x6B;
	const uint_fast8_t MPU_ADDR = 0x68;

	const uint8_t GYRO_CONFIG = 0x1B;
	const uint8_t GYRO_X_H = 0x43;
	const uint8_t ACCEL_CONFIG = 0x1C;
	const uint8_t ACCEL_X_H = 0x3B;

	const uint8_t SELF_TEST_X = 0x0D;
	const uint8_t SELF_TEST_Y = 0x0E;
	const uint8_t SELF_TEST_Z = 0x0F;

public:

	mpu6050 ( hwlib::i2c_bus_bit_banged_scl_sda mpu ):
		mpu (mpu)
	{
	}
}
