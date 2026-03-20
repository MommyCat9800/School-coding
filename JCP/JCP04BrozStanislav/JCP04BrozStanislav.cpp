#include <iostream>
#include <cstring>
using namespace std;

class Seznam {
        static Seznam *Prvni, *Iterator;
        char *jmeno;
        Seznam *dalsi;
    public:
        Seznam(const char *str) {
            jmeno = new char[strlen(str)+1];
            strcpy(jmeno, str);

            dalsi = Prvni;
            Prvni = this;
        }
        ~Seznam() {
            delete[] jmeno;
        }
        const char *jm() const {
            return jmeno;
        };
        static bool prvni() {
            if (Prvni != nullptr) {
                Iterator = Prvni;
                return true;
            }
            return false;
        }
        static const Seznam *soucasny() {
            return Iterator;
        }
        static bool posledni() {
            if (Iterator->dalsi == nullptr) {
                return true;
            }
            Iterator = Iterator->dalsi;
            return false;
        }
};

Seznam* Seznam::Prvni = nullptr;
Seznam* Seznam::Iterator = nullptr;

#include "U04"
int main() {
    T();
    return 0;
}