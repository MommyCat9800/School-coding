
#include <iostream>
#include <string>

using namespace std;
#include "U08"

void printName(int& currLineLen, int& maxLineLen, string currName) {
    if (currLineLen + currName.length() <= maxLineLen) {
        currLineLen += currName.length() + 1;
        cout << currName << " ";
    }
    else {
        cout << endl << currName << " ";
        currLineLen = currName.length() + 1;
    }
}

int main() {
    int maxLineLen;
    string currName;
    bool nameStarted = false;
    int currLineLen = 0;
    int namesLen = Jmena.length();
    cin >> maxLineLen;
    for (int i = 0; i < namesLen; i++) {
        if ( Jmena[i] >= 'A' && Jmena[i] <= 'Z') {
            if (!nameStarted) {
                currName.push_back( Jmena[i] );
            } else {
                printName(currLineLen, maxLineLen, currName);
                currName.clear();
                currName.push_back( Jmena[i] );
            }
            nameStarted = true;

        } else if ( Jmena[i] >= 'a' && Jmena[i] <= 'z') {
            currName.push_back( Jmena[i]);
        }
    }
    printName(currLineLen, maxLineLen, currName);

    return 1;
}
