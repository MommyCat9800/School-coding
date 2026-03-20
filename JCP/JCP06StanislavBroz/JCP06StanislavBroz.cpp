#include <iostream>
#include <cstring>
#include <cctype>
#include <cfloat>

struct Zbozi {
    char *nazev;
    float cena;

    Zbozi(const char *n, float c) {
        nazev = new char[strlen(n) + 1];
        strcpy(nazev, n);
        cena = c;
    }

    Zbozi() : nazev(nullptr), cena(0.0f) {}

    ~Zbozi() {
        delete[] nazev;
    }
};

typedef Zbozi *ZboziP;

class Cenik {
    ZboziP *zbozi;
    unsigned kapacita;
    unsigned pocet;

    bool shodaNazvu(const char *s1, const char *s2) const {
        if (!s1 || !s2) return false;
        while (*s1 && *s2) {
            if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2))
                return false;
            s1++;
            s2++;
        }
        return *s1 == *s2;
    }

public:
    Cenik(unsigned n) : kapacita(n), pocet(0) {
        zbozi = new ZboziP[kapacita];
        for (unsigned i = 0; i < kapacita; ++i) zbozi[i] = nullptr;
    }

    Cenik() : zbozi(nullptr), kapacita(0), pocet(0) {}

    ~Cenik() {
        for (unsigned i = 0; i < pocet; ++i) {
            delete zbozi[i];
        }
        delete[] zbozi;
    }

    int operator()(const char *nazev, float cena) {
        for (unsigned i = 0; i < pocet; ++i) {
            if (shodaNazvu(zbozi[i]->nazev, nazev)) {
                zbozi[i]->cena = cena;
                return -1;
            }
        }

        if (pocet < kapacita) {
            zbozi[pocet] = new Zbozi(nazev, cena);
            pocet++;
            return 1;
        }

        return 0;
    }

    bool operator()(const char *nazev) {
        for (unsigned i = 0; i < pocet; ++i) {
            if (shodaNazvu(zbozi[i]->nazev, nazev)) {
                delete zbozi[i];
                for (unsigned j = i; j < pocet - 1; ++j) {
                    zbozi[j] = zbozi[j + 1];
                }
                zbozi[pocet - 1] = nullptr;
                pocet--;
                return true;
            }
        }
        return false;
    }

    float operator[](const char *nazev) const {
        for (unsigned i = 0; i < pocet; ++i) {
            if (shodaNazvu(zbozi[i]->nazev, nazev)) {
                return zbozi[i]->cena;
            }
        }
        return FLT_MIN;
    }

    const Zbozi* operator[](unsigned index) const {
        if (index < pocet) {
            return zbozi[index];
        }
        return nullptr;
    }

    unsigned operator+() const {
        return pocet;
    }
};