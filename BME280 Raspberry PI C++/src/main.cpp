#include "bme280.h"

using namespace std;

int main()
{
    try
    {
        BME280 sensor;
        sensor.setup();

        float t = sensor.getTemperature();
        float p = sensor.getPressure();
        float h = sensor.getHumidity();
        float a = sensor.getAltitude(p);

        std::cout << "Sensor: bme280" << endl
             << "Humidity: " << h << endl
             << "Pressure: " << p << endl
             << "Temperature: " << t << endl
             << "Altitude: " << a << endl
             << "Timestamp: " << static_cast<int>(time(NULL)) << endl;
    }
    catch (const runtime_error &e)
    {
        cerr << e.what() << endl;
        return -1;
    }

    return 0;
}
