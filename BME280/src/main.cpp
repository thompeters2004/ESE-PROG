#include <Wire.h>
#include <BME280.h>
#include <Arduino.h>

BME280 bme280;
const int led = 9; //LED_BUILTIN;

void i2cWrite(uint8_t i2c_address, uint8_t *p_data, uint8_t data_size, uint8_t repeated_start)
{
  Wire.beginTransmission(i2c_address);
  Wire.write(p_data,data_size);
  Wire.endTransmission(repeated_start!=0?false:true);
}


void i2cRead(uint8_t i2c_address, uint8_t *p_data, uint8_t data_size)
{
  uint8_t i = 0;
  Wire.requestFrom(i2c_address,data_size);
  while (Wire.available() && i<data_size)
  {
    p_data[i] = Wire.read();
    i += 1;
  }
}


// Not using SPI, provide empty functions (stubs).
void spiWrite(uint8_t *p_data, uint8_t data_size) {}
void spiRead(uint8_t *p_data, uint8_t data_size) {}


void setup(void) 
{
  //Wire.setClock(100000);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
  
  Serial.println("Elektor project 150652");
  Serial.println("BME280 weather sensor");
  Serial.println();

  // Start the sensor driver and check if the sensor can be found.
  if (bme280.begin(BME280_I2C_ADDRESS2)!=0)
  {
    Serial.println("*** BME280 not found.");
    Serial.println();
  }
  
  // Configure sensor for test purposes.
  bme280.writeConfigRegister(BME280_STANDBY_500_US,BME280_FILTER_OFF,0);
  bme280.writeControlRegisters(BME280_OVERSAMPLING_1X,BME280_OVERSAMPLING_1X,BME280_OVERSAMPLING_1X,BME280_MODE_NORMAL);
}


void loop(void) 
{
  digitalWrite(led,HIGH);
  bme280.read();
  Serial.print("T=");
#if BME280_ALLOW_FLOAT!=0
  Serial.print(bme280.temperature());
#else
  Serial.print(bme280.temperature()/100);
#endif /* BME280_ALLOW_FLOAT */
  Serial.print(" degrees C, P=");
  Serial.print(bme280.pressure()/100);
  Serial.print(" mbar, RH=");
#if BME280_ALLOW_FLOAT!=0
  Serial.print(bme280.humidity());
#else
  Serial.print(bme280.humidity()>>10);
#endif /* BME280_ALLOW_FLOAT */
  Serial.println("%");
  delay(100);
  digitalWrite(led,LOW);
  delay(900);
}
