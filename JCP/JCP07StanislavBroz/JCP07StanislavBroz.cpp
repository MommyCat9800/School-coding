#include <iostream>

template<class P,class D>
class PFronta {
    private:
        P* priority;
        D* data;
        unsigned capacity;
        unsigned count;
    public:
        PFronta(unsigned rozsah) {
            capacity = rozsah;
            count=0;
            priority=new P[capacity];
            data=new D[capacity];
        };
        ~PFronta() {
            delete[] priority;
            delete[] data;
        };
        void pridat(const P &p,const D &d) {
            if (count == capacity) {
                unsigned newCapacity = capacity * 2;
                if (newCapacity == 0) newCapacity = 1;

                P* newPriority = new P[newCapacity];
                D* newData = new D[newCapacity];

                for (unsigned i=0; i<count; i++) {
                    newPriority[i] = priority[i];
                    newData[i] = data[i];
                }

                delete[] priority;
                delete[] data;

                capacity = newCapacity;
                priority = newPriority;
                data = newData;
            }
            priority[count] = p;
            data[count] = d;
            count++;
        };
        bool odebrat(D &output) {
            if (count == 0) {
                return false;
            }
            unsigned maxP = 0;
            for (unsigned i=0; i<count; i++) {
                if (priority[maxP] < priority[i]) {
                    // operator > nieje podla zadania pretazeny takze bolo nutno vymenit za operator <
                    maxP = i;
                }
            }
            output = data[maxP];
            count--;
            for (unsigned i = maxP; i<count; i++) {
                priority[i] = priority[i+1];
                data[i] = data[i+1];
            }
            return true;
        };
        unsigned operator + () const {
            return capacity;
        };
};


int main() {

    return 1;
}