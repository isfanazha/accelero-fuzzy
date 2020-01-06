//
// Created by isfanazha on 06/01/20.
//

#include "multiplexer.h"

void multiplexer::selector(char x) {
    switch (x) {
        case 1:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, HIGH);
            break;
        case 2:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S2, HIGH);
            break;

        case 3:
            digitalWrite(S0, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, HIGH);
            break;
        case 4:
            digitalWrite(S0, LOW);
            digitalWrite(S1, LOW);
            digitalWrite(S2, HIGH);
            break;
        case 5:
            digitalWrite(S0, LOW);
            digitalWrite(S1, HIGH);
            digitalWrite(S2, LOW);
            break;
        case 6:
            digitalWrite(S0, HIGH);
            digitalWrite(S1, LOW);
            digitalWrite(S2, LOW);
            break;
    }
}

multiplexer::multiplexer() {

}
