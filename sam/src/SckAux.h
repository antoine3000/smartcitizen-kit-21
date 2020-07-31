#pragma once

#include <SckBase.h>
#include <Sensors.h>

// Include the necessary libraries for the auxiliary sensor to be used
#include <Wire.h>
#include <FlashStorage.h>

// INA219 libs
#include <Adafruit_INA219.h>

// Gases Board libs
#include <GasesBoard.h>

// Urban board library
#include <SckUrban.h>

// Groove_OLED libs
#include <U8g2lib.h>

// DS2482 library (I2C-1Wire bridge)
#include <DS2482.h>

// I2C Moisture Sensor (chirp)
#include <I2CSoilMoistureSensor.h>

// Libraries for DallasTemp
#include <OneWire.h>
#include <DallasTemperature.h>

// Sparkfun VL6180x time of flight range finder
#include <SparkFun_VL6180X.h>

// Adafruit BME608 library
#include <Adafruit_BME680.h>

// Library for GPS data parsing
#include "TinyGPS++.h"

// Librtary for XA1110 Sparkfun i2c GPS
#include <SparkFun_I2C_GPS_Arduino_Library.h>

// Library for SparkFun u-Blox NEO-M8U GPS
#include "SparkFun_Ublox_Arduino_Library.h"

// Adafruit library for ADS1x15 12/16 bits ADC
#include <Adafruit_ADS1015.h>


extern TwoWire auxWire;

class SckBase;


struct Calibration {
	bool  moistureCalDataValid = false;
	int32_t dryPoint;
	int32_t wetPoint;
};

struct EepromAuxData {
	bool valid = false;
	Calibration calibration;
};

bool I2Cdetect(byte address);

class AuxBoards
{

	public:

		// List for storing Auxiliary sensors I2C address (SENSOR_COUNT - (BASE AND URBAN SENSORS))
		// TODO: store this in epprom, load it on boot, make a function to change the addresses by console command
		byte devAddress[SENSOR_COUNT - 24] {
			0x55,			// SENSOR_GASESBOARD_SLOT_1A,
			0x55,			// SENSOR_GASESBOARD_SLOT_1W,
			0x56,			// SENSOR_GASESBOARD_SLOT_2A,
			0x56,			// SENSOR_GASESBOARD_SLOT_2W,
			0x54,			// SENSOR_GASESBOARD_SLOT_3A,
			0x54,			// SENSOR_GASESBOARD_SLOT_3W,
			0x44,			// SENSOR_GASESBOARD_TEMPERATURE,
			0x44,			// SENSOR_GASESBOARD_HUMIDITY,

			0x59,			// SENSOR_GROOVE_I2C_ADC,

			0x41,			// SENSOR_INA219_BUSVOLT,
			0x41,			// SENSOR_INA219_SHUNT,
			0x41,			// SENSOR_INA219_CURRENT,
			0x41,			// SENSOR_INA219_LOADVOLT,

			0x18, 			// SENSOR_WATER_TEMP_DS18B20,
			0x66,			// SENSOR_ATLAS_TEMPERATURE,
			0x63,			// SENSOR_ATLAS_PH,
			0x64,			// SENSOR_ATLAS_EC,
			0x64,			// SENSOR_ATLAS_EC_SG,
			0x61,			// SENSOR_ATLAS_DO,
			0x61,			// SENSOR_ATLAS_DO_SAT,

			0x20,			// SENSOR_CHIRP_MOISTURE_RAW,
			0x20,			// SENSOR_CHIRP_MOISTURE,
			0x20,			// SENSOR_CHIRP_TEMPERATURE,
			0x20,			// SENSOR_CHIRP_LIGHT,

			0x02,			// SENSOR_EXT_PM_1,
			0x02,			// SENSOR_EXT_PM_25,
			0x02,			// SENSOR_EXT_PM_10,
			0x02,			// SENSOR_EXT_PN_03,
			0x02,			// SENSOR_EXT_PN_05,
			0x02,			// SENSOR_EXT_PN_1,
			0x02,			// SENSOR_EXT_PN_25,
			0x02,			// SENSOR_EXT_PN_5,
			0x02,			// SENSOR_EXT_PN_10,
			0x02,			// SENSOR_EXT_A_PM_1,
			0x02,			// SENSOR_EXT_A_PM_25,
			0x02,			// SENSOR_EXT_A_PM_10,
			0x02,			// SENSOR_EXT_A_PN_03,
			0x02,			// SENSOR_EXT_A_PN_05,
			0x02,			// SENSOR_EXT_A_PN_1,
			0x02,			// SENSOR_EXT_A_PN_25,
			0x02,			// SENSOR_EXT_A_PN_5,
			0x02,			// SENSOR_EXT_A_PN_10,
			0x02,			// SENSOR_EXT_B_PM_1,
			0x02,			// SENSOR_EXT_B_PM_25,
			0x02,			// SENSOR_EXT_B_PM_10,
			0x02,			// SENSOR_EXT_B_PN_03,
			0x02,			// SENSOR_EXT_B_PN_05,
			0x02,			// SENSOR_EXT_B_PN_1,
			0x02,			// SENSOR_EXT_B_PN_25,
			0x02,			// SENSOR_EXT_B_PN_5,
			0x02,			// SENSOR_EXT_B_PN_10,

			0x02,			// SENSOR_PM_DALLAS_TEMP,
			0x00,			// SENSOR_DALLAS_TEMP, 		-- 2 wire (no I2C address)

			0x44,			// SENSOR_SHT31_TEMP,
			0x44,			// SENSOR_SHT31_HUM,

			0x29,			// SENSOR_RANGE_LIGHT,
			0x29,			// SENSOR_RANGE_DISTANCE,

			0x77,			// SENSOR_BME680_TEMPERATURE,
			0x77,			// SENSOR_BME680_HUMIDITY,
			0x77,			// SENSOR_BME680_PRESSURE,
			0x77,			// SENSOR_BME680_VOCS,

			0x02, 			// SENSOR_GPS_* Grove Gps (on PM board)
			0x10, 			// SENSOR_GPS_* XA111 Gps
			0x42, 			// SENSOR_GPS_* NEO-M8U Gps

			0x3c,			// SENSOR_GROOVE_OLED,

			0x48, 			// SENSOR_ADS1X15_XX_X
			0x49, 			// SENSOR_ADS1X15_XX_X
			0x4a, 			// SENSOR_ADS1X15_XX_X
			0x4b 			// SENSOR_ADS1X15_XX_X
		};

		bool start(SensorType wichSensor);
		bool stop(SensorType wichSensor);
		void getReading(SckBase *base, OneSensor *wichSensor);
		bool getBusyState(SensorType wichSensor);
		String control(SensorType wichSensor, String command);
		void print(SensorType wichSensor, String payload);
		void displayReading(String title, String reading, String unit, String time);

		EepromAuxData data;
		bool dataLoaded = false;
	private:
};

class GrooveI2C_ADC
{
	public:

		bool start();
		bool stop();
		float getReading();

		const byte deviceAddress 	= 0x59;
		const float V_REF 		= 3.30;
		const byte REG_ADDR_RESULT	= 0x00;
		const byte REG_ADDR_ALERT	= 0x01;
		const byte REG_ADDR_CONFIG	= 0x02;
		const byte REG_ADDR_LIMITL	= 0x03;
		const byte REG_ADDR_LIMITH	= 0x04;
		const byte REG_ADDR_HYST	= 0x05;
		const byte REG_ADDR_CONVL	= 0x06;
		const byte REG_ADDR_CONVH	= 0x07;

	private:
};

class INA219
{
	public:

		const byte deviceAddress = 0x41;

		enum typeOfReading {BUS_VOLT, SHUNT_VOLT, CURRENT, LOAD_VOLT};

		Adafruit_INA219 ada_ina219 = Adafruit_INA219(deviceAddress);
		bool start();
		bool stop();
		float getReading(typeOfReading wichReading=CURRENT);

	private:
};

static const unsigned char scLogo[] PROGMEM =
{
	0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xff, 0x3f, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xff, 0x07, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xf8, 0xff, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xfc, 0x7f, 0x00, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xfe, 0x1f, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0x0f, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0xff, 0x03, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00,
	0x00, 0x80, 0xff, 0x01, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00,
	0x00, 0xc0, 0xff, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xc0, 0x07, 0x00,
	0x00, 0xe0, 0x7f, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00,
	0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00,
	0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0x00,
	0x00, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00,
	0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x3f, 0x00,
	0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x00,
	0x00, 0xfe, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x00,
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x01,
	0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01,
	0x80, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01,
	0x80, 0x7f, 0xc0, 0xc3, 0x00, 0x03, 0x07, 0x7e, 0xf8, 0x07, 0xfe, 0x03,
	0x80, 0x7f, 0xe0, 0xc7, 0x00, 0x03, 0x07, 0xfe, 0xf8, 0x07, 0xfe, 0x03,
	0xc0, 0x3f, 0x70, 0xce, 0x00, 0x03, 0x07, 0xee, 0xf9, 0x07, 0xfc, 0x03,
	0xc0, 0x3f, 0x30, 0xcc, 0x81, 0x83, 0x0f, 0xc6, 0xc1, 0x00, 0xfc, 0x03,
	0xc0, 0x3f, 0x30, 0xc0, 0x81, 0x83, 0x0f, 0x86, 0xc1, 0x00, 0xfc, 0x07,
	0xc0, 0x1f, 0x30, 0xc0, 0x81, 0x83, 0x0d, 0x86, 0xc1, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x70, 0xc0, 0xc3, 0x83, 0x0d, 0x86, 0xc1, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0xe0, 0xc0, 0xc3, 0xc3, 0x1d, 0xc6, 0xc1, 0x00, 0xf8, 0x07,
	0xe0, 0x1f, 0xc0, 0xc1, 0xe7, 0xc3, 0x18, 0xee, 0xc1, 0x00, 0xf8, 0x07,
	0xe0, 0x1f, 0x80, 0xc3, 0x66, 0xc3, 0x18, 0xfe, 0xc0, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0x00, 0xc7, 0x66, 0xc3, 0x18, 0x7e, 0xc0, 0x00, 0xf8, 0x0f,
	0xe0, 0x0f, 0x00, 0xce, 0x7e, 0xe3, 0x38, 0x66, 0xc0, 0x00, 0xf8, 0x0f,
	0xe0, 0x0f, 0x00, 0xcc, 0x3c, 0xe3, 0x3f, 0xe6, 0xc0, 0x00, 0xf0, 0x0f,
	0xe0, 0x0f, 0x30, 0xcc, 0x3c, 0xe3, 0x3f, 0xc6, 0xc0, 0x00, 0xf0, 0x0f,
	0xe0, 0x0f, 0x30, 0xcc, 0x18, 0x63, 0x30, 0xc6, 0xc0, 0x00, 0xf0, 0x0f,
	0xe0, 0x0f, 0x70, 0xc7, 0x18, 0x63, 0x30, 0xc6, 0xc1, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0xe0, 0xc7, 0x18, 0x63, 0x30, 0x86, 0xc1, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0xc0, 0xc3, 0x00, 0x63, 0x30, 0x86, 0xc1, 0x00, 0xf8, 0x0f,
	0xe0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x00, 0x70, 0xec, 0x37, 0x9f, 0x6f, 0x0c, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x00, 0xf8, 0xec, 0x37, 0x9f, 0x6f, 0x0c, 0x00, 0xf8, 0x07,
	0xc0, 0x1f, 0x00, 0xd8, 0x8c, 0x31, 0x98, 0xe1, 0x0c, 0x00, 0xf8, 0x07,
	0xc0, 0x3f, 0x00, 0xd8, 0x8c, 0x31, 0x9c, 0xe1, 0x0c, 0x00, 0xfc, 0x07,
	0xc0, 0x3f, 0x00, 0x18, 0x8c, 0x31, 0x8c, 0xe1, 0x0d, 0x00, 0xfc, 0x03,
	0xc0, 0x3f, 0x00, 0x18, 0x8c, 0x31, 0x8e, 0xe7, 0x0d, 0x00, 0xfc, 0x03,
	0x80, 0x7f, 0x00, 0x18, 0x8c, 0x31, 0x86, 0x67, 0x0f, 0x00, 0xfe, 0x03,
	0x80, 0x7f, 0x00, 0x18, 0x8c, 0x31, 0x86, 0x61, 0x0f, 0x00, 0xfe, 0x03,
	0x80, 0xff, 0x00, 0xd8, 0x8c, 0x31, 0x87, 0x61, 0x0e, 0x00, 0xff, 0x01,
	0x00, 0xff, 0x00, 0xd8, 0x8c, 0x31, 0x83, 0x61, 0x0e, 0x00, 0xff, 0x01,
	0x00, 0xff, 0x01, 0xf8, 0x8c, 0x31, 0x9f, 0x6f, 0x0c, 0x80, 0xff, 0x01,
	0x00, 0xfe, 0x01, 0x70, 0x8c, 0x31, 0x9f, 0x6f, 0x0c, 0x80, 0xff, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x00,
	0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7f, 0x00,
	0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00,
	0x00, 0xfc, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00,
	0x00, 0xf8, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x3f, 0x00,
	0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x1f, 0x00,
	0x00, 0xf0, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x1f, 0x00,
	0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x0f, 0x00,
	0x00, 0xc0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x00,
	0x00, 0x80, 0xff, 0x03, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0x03, 0x00,
	0x00, 0x80, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x01, 0x00,
	0x00, 0x00, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x00, 0x00,
	0x00, 0x00, 0xfe, 0x1f, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x00, 0x00,
	0x00, 0x00, 0xfc, 0x7f, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x7f, 0x00, 0x00,
	0x00, 0x00, 0xf8, 0xff, 0x01, 0x00, 0x00, 0x80, 0xff, 0x3f, 0x00, 0x00,
	0x00, 0x00, 0xf0, 0xff, 0x0f, 0x00, 0x00, 0xf0, 0xff, 0x1f, 0x00, 0x00,
	0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0xfe, 0xff, 0x07, 0x00, 0x00,
	0x00, 0x00, 0x80, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00
};

class Groove_OLED
{
	public:

		const byte deviceAddress = 0x3c;

		U8G2_SSD1327_SEEED_96X96_F_HW_I2C U8g2_oled = U8G2_SSD1327_SEEED_96X96_F_HW_I2C(U8G2_R0, U8X8_PIN_NONE, SCL, SDA);

		bool start();
		bool stop();
		void print(String payload);
		void displayReading(String title, String reading, String unit, String time);

	private:
};

/*! @class DS2482_100
 *  @brief class for handling the DS18B20 temperature sensor connected to the I2C port
 *   through the DS2482-100 board. This was based on an example made by
 *   <a href="https://github.com/paeaetech/paeae.git">paeae</a>
 */
class WaterTemp_DS18B20
{

	public:

		byte deviceAddress = 0x18;

		DS2482 DS_bridge = DS2482(0);

		byte data[8];
		byte addr[8];

		uint8_t conf =0x05;

		bool detected = false;

		/* Start the transmission of data for the DS18B20 trough the DS2482_100 bridge */
		bool start();
		bool stop();
		/* Read the temperature of the DS18B20 through the DS2482_100 bridge */
		/* @return Temperature */
		float getReading();
	private:
};

class Atlas
{
	public:

		byte deviceAddress;
		SensorType atlasType;
		bool PH = false;
		bool EC = false;
		bool DO = false;
		bool TEMP = false;
		float newReading[4];
		String atlasResponse;
		uint32_t lastCommandSent = 0;
		uint32_t lastUpdate = 0;
		enum State {
			REST,
			TEMP_COMP_SENT,
			ASKED_READING,
		};
		State state = REST;

		// Constructor varies by sensor type
		Atlas(SensorType wichSensor) {
			atlasType = wichSensor;

			switch(atlasType) {
				case SENSOR_ATLAS_PH: {

						deviceAddress = 0x63;
						PH = true;
						break;

					} case SENSOR_ATLAS_EC:
					case SENSOR_ATLAS_EC_TDS:
					case SENSOR_ATLAS_EC_SAL:
					case SENSOR_ATLAS_EC_SG: {

						deviceAddress = 0x64;
						EC = true;
						break;

					} case SENSOR_ATLAS_DO:
					case SENSOR_ATLAS_DO_SAT: {

						deviceAddress = 0x61;
						DO = true;
						break;

					} case SENSOR_ATLAS_TEMPERATURE: {

						deviceAddress = 0x66;
						TEMP = true;
						break;

					} default: break;
			}

		}

		bool start();
		bool beginDone = false;
		bool stop();
		bool getReading();
		bool getBusyState();

		void goToSleep();
		bool sendCommand(char* command);
		bool tempCompensation();
		uint8_t getResponse();

		uint16_t longWait = 910; //ms
		uint16_t mediumWait = 610; //ms
		uint16_t shortWait = 310; //ms

		bool detected = false;

	private:
};

class Moisture
{
	private:
		byte deviceAddress = 0x20;
		I2CSoilMoistureSensor chirp = I2CSoilMoistureSensor(deviceAddress);
		bool alreadyStarted = false;

	public:
		bool detected = false;
		bool calibrated = false;
		int32_t dryPoint;
		int32_t wetPoint;

		bool start();
		bool stop();
		bool getReading(SensorType wichSensor);
		uint8_t getVersion();
		bool resetAddress(int currentAddress);

		uint32_t raw;
		float moisture;
		int16_t temperature;
		int32_t light;

		// TODO
		// * Measure sensor consumption
		// * Send sensor to sleep between readings (needs FIX, it hangs)
		void sleep();
};

enum PMslot {SLOT_A, SLOT_B, SLOT_AVG};
enum PMcommands
{
	PM_START,        // Start both PMS
	GET_PMA,         // Get values for PMS in slot A
	GET_PMB,         // Get values for PMS in slot A
	GET_PM_AVG,      // Get values for both PMS averaged
	PM_STOP,         // Stop both PMS
	DALLASTEMP_START,
	DALLASTEMP_STOP,
	GET_DALLASTEMP,
	GROVEGPS_START,
	GROVEGPS_STOP,
	GROVEGPS_GET
 };

class PMsensor
{
	public:

		const byte deviceAddress = 0x02;

		uint16_t pm1;
		uint16_t pm25;
		uint16_t pm10;
		uint16_t pn03;
		uint16_t pn05;
		uint16_t pn1;
		uint16_t pn25;
		uint16_t pn5;
		uint16_t pn10;

		bool start();
		bool stop();
		float getReading(PMslot slot, SensorType wichSensor);
	private:
		bool started = false;
		bool failed = false;

		static const uint8_t valuesSize = 18;
		uint8_t values[valuesSize];

		// 24 bytes:
		// 0:1->pm1, 2:3->pm25, 4:5->pm10,
		// Number of particles with diameter beyond X um in 0.1 L of air.
		// 6:7 -> 0.3 um
		// 8:9 -> 0.5 um
		// 10:11 -> 1.0 um
		// 12:13 -> 2.5 um
		// 14:15 -> 5.0 um
		// 16:17 -> 10.0 um
		//
		uint32_t lastReading = 0;
		PMslot lastSlot;
};

class PM_DallasTemp
{
	public:
		const byte deviceAddress = 0x02;
		bool start();
		bool stop();
		float getReading();
	private:
		union u_reading {
			byte b[4];
			float fval;
		} uRead;

		float reading;
};

struct GpsReadings
{
	// Data (40 bytes)
	// Fix Quality -> uint8 - 1
	// 	0 = Invalid
	// 	1 = GPS fix (SPS)
	// 	2 = DGPS fix
	// 	3 = PPS fix
	// 	4 = Real Time Kinematic
	// 	5 = Float RTK
	// 	6 = estimated (dead reckoning) (2.3 feature)
	// 	7 = Manual input mode
	// 	8 = Simulation mode
	// locationValid -> bool - 1
	// Latitude DDD.DDDDDD (negative is south) -> double - 8
	// Longitude DDD.DDDDDD (negative is west) -> double - 8
	// altitudeValid -> bool - 1
	// Altitude in meters -> float - 4
	// timeValid -> bool - 1
	// Time (epoch) -> uint32 - 4
	// speedValid -> bool - 1
	// Speed (meters per second) -> float - 4
	// hdopValid -> bool - 1
	// Horizontal dilution of position -> float - 4
	// satellitesValid -> bool - 1
	// Number of Satellites being traked -> uint8 - 1

	uint8_t fixQuality = 0;
	bool locationValid = false;
	double latitude;
	double longitude;
	bool altitudeValid = false;
	float altitude;
	bool speedValid = false;
	float speed;
	bool hdopValid = false;
	float hdop;
	bool satellitesValid = false;
	uint8_t satellites;
	bool timeValid = false;
	uint32_t epochTime = 0;
};

class GPS_Source
{
	public:
		virtual bool stop();
		virtual bool getReading(SensorType wichSensor, GpsReadings &r);
};

class Sck_GPS
{
	private:
		bool started = false;
		uint8_t fixCounter = 0;
		GPS_Source *gps_source;
	public:
		GpsReadings r;

		bool start();
		bool stop();
		bool getReading(SckBase *base, SensorType wichSensor);
};

class PM_Grove_GPS: public GPS_Source
{
	public:
		const byte deviceAddress = 0x02;

		bool start();
		virtual bool stop();
		virtual bool getReading(SensorType wichSensor, GpsReadings &r);

	private:
		static const uint8_t DATA_LEN = 40;
		byte data[DATA_LEN];
		uint32_t lastReading = 0;
};

class XA111GPS: public GPS_Source
{
	public:
		const byte deviceAddress = 0x10;

		bool start();
		virtual bool stop();
		virtual bool getReading(SensorType wichSensor, GpsReadings &r);

	private:
		I2CGPS i2cGps;
		uint32_t lastReading = 0;

};

class NEOM8UGPS: public GPS_Source
{
	public:
		const byte deviceAddress = 0x42;

		bool start();
		virtual bool stop();
		virtual bool getReading(SensorType wichSensor, GpsReadings &r);

	private:
		SFE_UBLOX_GPS ubloxGps;
		uint32_t lastReading = 0;

};

class Sck_DallasTemp
{
	// This is for a Dallas temperature sensor connected to the plugged in Aux groove connector using pin pinAUX_WIRE_SCL (13 - PA17)
	public:
		bool start();
		bool stop();
		bool getReading();

		float reading;
	private:
		uint8_t _oneWireAddress[8];
};

class Sck_Range
{
	public:
		const byte deviceAddress = 0x29;
		bool start();
		bool stop();
		bool getReading(SensorType wichSensor);

		float readingLight;
		float readingDistance;
	private:

		bool alreadyStarted = false;
		VL6180x vl6180x = VL6180x(deviceAddress);
};

class Sck_BME680
{
	public:
		const byte deviceAddress = 0x77;
		bool start();
		bool stop();
		bool getReading();

		float temperature;
		float humidity;
		float pressure;
		float VOCgas;
	private:
		uint32_t lastTime = 0;
		uint32_t minTime = 1000; 	// Avoid taking readings more often than this value (ms)
		bool alreadyStarted = false;
		Adafruit_BME680 bme;
};

class Sck_ADS1X15
{
	public:
		const byte deviceAddress = 0x48;
		bool start(uint8_t address);
		bool stop();
		bool getReading(uint8_t wichChannel);

		float reading;
	private:
		float VOLTAGE = 3.3;
		bool started = false;
		Adafruit_ADS1115 ads = Adafruit_ADS1115(&auxWire);

	// TODO
	// Test ADS1015
};

void writeI2C(byte deviceAddress, byte instruction, byte data);
byte readI2C(byte deviceAddress, byte instruction);
