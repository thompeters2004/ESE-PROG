#include "bme280.h"

using namespace std;

BME280::BME280() {
    fd = -1;
}

bool BME280::initialize() {
    fd = wiringPiI2CSetup(BME280_ADDRESS);
    if(fd < 0) {
        return false;
    }
    readCalibrationData();
    return true;
}

void BME280::readCalibrationData() {
data->dig_T1 = (uint16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_T1);
  data->dig_T2 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_T2);
  data->dig_T3 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_T3);

  data->dig_P1 = (uint16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P1);
  data->dig_P2 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P2);
  data->dig_P3 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P3);
  data->dig_P4 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P4);
  data->dig_P5 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P5);
  data->dig_P6 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P6);
  data->dig_P7 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P7);
  data->dig_P8 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P8);
  data->dig_P9 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_P9);

  data->dig_H1 = (uint8_t)wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H1);
  data->dig_H2 = (int16_t)wiringPiI2CReadReg16(fd, BME280_REGISTER_DIG_H2);
  data->dig_H3 = (uint8_t)wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H3);
  data->dig_H4 = (wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H4) << 4) | (wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H4+1) & 0xF);
  data->dig_H5 = (wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H5+1) << 4) | (wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H5) >> 4);
  data->dig_H6 = (int8_t)wiringPiI2CReadReg8(fd, BME280_REGISTER_DIG_H6);
}

int32_t BME280::getTemperatureCalibration(int32_t adc_T) {
  int32_t var1  = ((((adc_T>>3) - ((int32_t)cal->dig_T1 <<1))) *
     ((int32_t)cal->dig_T2)) >> 11;

  int32_t var2  = (((((adc_T>>4) - ((int32_t)cal->dig_T1)) *
       ((adc_T>>4) - ((int32_t)cal->dig_T1))) >> 12) *
     ((int32_t)cal->dig_T3)) >> 14;

  return var1 + var2;}

float BME280::compensateTemperature(int32_t t_fine) {
  float T  = (t_fine * 5 + 128) >> 8;
  return T/100;
}

float BME280::compensatePressure(int32_t adc_P, int32_t t_fine) {
  int64_t var1, var2, p;

  var1 = ((int64_t)t_fine) - 128000;
  var2 = var1 * var1 * (int64_t)cal->dig_P6;
  var2 = var2 + ((var1*(int64_t)cal->dig_P5)<<17);
  var2 = var2 + (((int64_t)cal->dig_P4)<<35);
  var1 = ((var1 * var1 * (int64_t)cal->dig_P3)>>8) +
    ((var1 * (int64_t)cal->dig_P2)<<12);
  var1 = (((((int64_t)1)<<47)+var1))*((int64_t)cal->dig_P1)>>33;

  if (var1 == 0) {
    return 0;  // avoid exception caused by division by zero
  }
  p = 1048576 - adc_P;
  p = (((p<<31) - var2)*3125) / var1;
  var1 = (((int64_t)cal->dig_P9) * (p>>13) * (p>>13)) >> 25;
  var2 = (((int64_t)cal->dig_P8) * p) >> 19;

  p = ((p + var1 + var2) >> 8) + (((int64_t)cal->dig_P7)<<4);
  return (float)p/256;}

float BME280::compensateHumidity(int32_t adc_H, int32_t t_fine) {
      int32_t v_x1_u32r;

  v_x1_u32r = (t_fine - ((int32_t)76800));

  v_x1_u32r = (((((adc_H << 14) - (((int32_t)cal->dig_H4) << 20) -
      (((int32_t)cal->dig_H5) * v_x1_u32r)) + ((int32_t)16384)) >> 15) *
         (((((((v_x1_u32r * ((int32_t)cal->dig_H6)) >> 10) *
        (((v_x1_u32r * ((int32_t)cal->dig_H3)) >> 11) + ((int32_t)32768))) >> 10) +
      ((int32_t)2097152)) * ((int32_t)cal->dig_H2) + 8192) >> 14));

  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *
           ((int32_t)cal->dig_H1)) >> 4));

  v_x1_u32r = (v_x1_u32r < 0) ? 0 : v_x1_u32r;
  v_x1_u32r = (v_x1_u32r > 419430400) ? 419430400 : v_x1_u32r;
  float h = (v_x1_u32r>>12);
  return  h / 1024.0;
}

void BME280::getRawData(bme280_raw_data *raw) {
    wiringPiI2CWrite(fd, 0xf7);

  raw->pmsb = wiringPiI2CRead(fd);
  raw->plsb = wiringPiI2CRead(fd);
  raw->pxsb = wiringPiI2CRead(fd);

  raw->tmsb = wiringPiI2CRead(fd);
  raw->tlsb = wiringPiI2CRead(fd);
  raw->txsb = wiringPiI2CRead(fd);

  raw->hmsb = wiringPiI2CRead(fd);
  raw->hlsb = wiringPiI2CRead(fd);

  raw->temperature = 0;
  raw->temperature = (raw->temperature | raw->tmsb) << 8;
  raw->temperature = (raw->temperature | raw->tlsb) << 8;
  raw->temperature = (raw->temperature | raw->txsb) >> 4;

  raw->pressure = 0;
  raw->pressure = (raw->pressure | raw->pmsb) << 8;
  raw->pressure = (raw->pressure | raw->plsb) << 8;
  raw->pressure = (raw->pressure | raw->pxsb) >> 4;

  raw->humidity = 0;
  raw->humidity = (raw->humidity | raw->hmsb) << 8;
  raw->humidity = (raw->humidity | raw->hlsb);
}

float BME280::getTemperature() {
    bme280_raw_data raw;
    getRawData(&raw);
    int32_t t_fine = getTemperatureCalibration(raw.temperature);
    return compensateTemperature(t_fine);
}

float BME280::getPressure() {
    bme280_raw_data raw;
    getRawData(&raw);
    int32_t t_fine = getTemperatureCalibration(raw.temperature);
    return compensatePressure(raw.pressure, t_fine) / 100;
}

float BME280::getHumidity() {
    bme280_raw_data raw;
    getRawData(&raw);
    int32_t t_fine = getTemperatureCalibration(raw.temperature);
    return compensateHumidity(raw.humidity, t_fine);
}

float BME280::getAltitude() {
    float p = getPressure();
    return 44330.0 * (1.0 - pow(p / MEAN_SEA_LEVEL_PRESSURE, 0.190294957));
}
