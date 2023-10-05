#include "bme280.h"

using namespace std;

int main() {
    BME280 sensor;

    if(!sensor.initialize()) {
        cout << "Device not found" << endl;
        return -1;
    }

    float t = sensor.getTemperature(); // C
    float p = sensor.getPressure();    // hPa
    float h = sensor.getHumidity();    // %
    float a = sensor.getAltitude();    // meters

    cout << "Sensor: bme280" << endl
         << "Humidity: " << h << endl
         << "Pressure: " << p << endl
         << "Temperature: " << t << endl 
         << "Altitude: " << a << endl 
         << "Timestamp: " << static_cast<int>(time(NULL)) << endl;

    return 0;
}
