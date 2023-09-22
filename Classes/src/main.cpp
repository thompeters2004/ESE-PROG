#include "main.h"

using namespace std;

class Car
{
private:
    string brand;
    string color;
    int age;

public:
    void setBrand(const string& Brand) { brand = Brand; }
    void setColor(const string& Color) { color = Color; }
    void setAge(int Age) { age = Age; }

    string getBrand() const { return brand; }
    string getColor() const { return color; }
    int getAge() const { return age; }
};

int main(){
    Car Opel;
    Opel.setAge(2004);
    Opel.setColor("White");
    Opel.setBrand("Opel");

    cout << "Brand: " << Opel.getBrand() << ", Color: " << Opel.getColor() << ", Age: " << Opel.getAge() << endl;

    return 0;
}
