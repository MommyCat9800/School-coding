#include <iostream>
#include <cmath>
#include <iomanip>


using namespace std;

class Cm {
    double hodnota;
    public:
    Cm(double x) {hodnota = x;}
    double cm() {return hodnota;}
    double palec() {return hodnota / 2.54;}
    double rozdil(Cm &val) {return fabs(hodnota - val.cm());}
    double rozdil(class Palec &val);
};

class Palec {
    double hodnota;
public:
    Palec(double x) {hodnota = x;}
    double palec() {return hodnota;}
    double cm() {return hodnota * 2.54;}
    double rozdil(class Palec &val) {}
    double rozdil(class Cm &val) {return fabs(cm() - val.cm());}
};

double Cm::rozdil(class Palec &val) {
    return fabs(palec() - val.palec());
}


int main() {
    Cm a(2),b(2.5);
    Palec u(1), v(1.5);

    cout << setprecision(4);

    cout << left << setw(15) << "a=2 cm"
         << setw(20) << "b=0.9843 palce"
         << "b-a=" << b.rozdil(a) << " cm"
         << right << setw(20) << "a-u=0.2126 palce" << endl;

    cout << left << setw(15) << "u=2.54 cm"
         << setw(20) << "v=1.5 palce"
         << "u-v=" << u.rozdil(v) << " palce"
         << right << setw(18) << "u-b=0.04 cm" << endl;

    return 0;
}

