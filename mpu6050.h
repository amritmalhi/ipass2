/**
 * @class mpu6050
 * @author Amrit Malhi 1691806
 * @file mpu6050.h
 * @brief Interface abstraction of MPU6050 Gyro and Accelerometer

 * Features include reading initalization of sensor, reading of both sensors
 * and calibration of gyro. 
 * Note: sensor must be initialized by using init(); before calling any function which
 * manipulates the sensor.
 *
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MPU6050_HPP
#define MPU6050_HPP

#define RAD_TO_DEG 57.3

#include "hwlib.hpp"
#include "math.h"

class mpu6050 {
private:

	hwlib::i2c_bus bus;
	uint_fast8_t address; // i2c address of sensor
	
	/**
	*	Data Register Addresses for the MPU6050
	* 	Refer to MPU6050 Register Map and Descriptions document
	* 	for more information.
	* */

	static constexpr const uint8_t PWR_MGMT_1 = 0x6B;
	static constexpr const uint8_t GYRO_CONFIG = 0x1B;
	static constexpr const uint8_t ACC_CONFIG = 0x1C;
	static constexpr const uint8_t ACC_OUT = 0x3B;  
	static constexpr const uint8_t GYRO_OUT = 0x43;	
	
	/**
	*	Commands for initialization of the sensor
	*/

	static const uint8_t CLK_SLCT[2] = {PWR_MGMT_1, 0x01}; // Wake up device with Y Gyro as reference clock
	const uint8_t GYRO_RNG[2] = {GYRO_CONFIG, 0x08}; // Set Gyroscope full range to ± 250 °/s 
	const uint8_t ACC_RNG[2] = {ACC_CONFIG, 0x00}; // Set Accelerometer full scale range to ± 2g

	/**
	*	For calibration purposes
	*/
	
	int16_t gX_offset = 0, gY_offset = 0, gZ_offset = 0;
	double roll_offset = 0.0, pitch_offset = 0.0; 

public:

	/**
	*	Accelerometer and Gyroscope values
	*/
	 
	int16_t acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z;
	
	/**
	* @brief Constructor
	* @param mpu 	i2c bus connected to mpu6050
	*/
	
	mpu6050 ( hwlib::i2c_bus bus, const uint_fast8_t address = 0x68 ):
		bus (bus),
		address (address)
	{
		static constexpr const uint8_t init_sequence[] = {
			CLK_SLCT, 
			ACC_RNG,
			GYRO_RNG
		};

		bus.write (
			address,
			init_sequence,
			sizeof ( init_sequence ) / sizeof ( uint8_t )
		);
	}
	
	/**
	* @brief Reads current Gyroscope values
	*/
	
	void get_gyro () {
		uint8_t values[6];
		mpu.write(MPU_ADDR, & GYRO_OUT, 1);
		mpu.read(MPU_ADDR, values, 6);
		gyro_x = (int16_t) (values[0]<<8|values[1]);
		gyro_y = (int16_t) (values[2]<<8|values[3]);
		gyro_z = (int16_t) (values[4]<<8|values[5]);
	}
	
	/**
	 * @brief Reads current Accelerometer values 
	 */
	
	void get_acc () {
		uint8_t values[6];
		mpu.write(MPU_ADDR, & ACC_OUT, 1);
		mpu.read(MPU_ADDR, values, 6);

		acc_x = (int16_t) values[0]<<8|values[1];
		acc_y = (int16_t) values[2]<<8|values[3];
		acc_z = (int16_t) values[4]<<8|values[5];
	}
	
	/**
	* @brief Reads both Accelerometer and Gyroscope values from MPU6050.
	*/
	
	void get_both () {
		uint8_t values[14];
		mpu.write(MPU_ADDR, & ACC_OUT, 1);
		mpu.read(MPU_ADDR, values, 14);

		acc_x = (int16_t) values[0]<<8|values[1];
		acc_y = (int16_t) values[2]<<8|values[3];
		acc_z = (int16_t) values[4]<<8|values[5];
		gyro_x = (int16_t) (values[8]<<8|values[9]) - gX_offset;
		gyro_y = (int16_t) (values[10]<<8|values[11]) - gY_offset;
		gyro_z = (int16_t) (values[12]<<8|values[13]) - gZ_offset;
	}
	
	/**
	* @brief Calibration function for Gyroscope
	* @param n	Amount of calibrations to complete
	*/
	
	void calibrate_gyro (uint16_t n = 1000 ) {
		int32_t gX = 0, gY = 0, gZ = 0;
		
		for (int i = 0; i < n; i++) {
			get_gyro();
			gX += gX_offset;
			gY += gY_offset;
			gZ += gZ_offset;
		}
		
		gX_offset = gX / n;
		gY_offset = gY / n;
		gZ_offset = gZ / n;
	}
};

#endif
