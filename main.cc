/**
 * Generated with sketch 0.4.1
 **/
#include "main.h"

void ledStatus(void) {
    static uint8_t counter = 0;

    counter++;
    if(counter == millis(200) || counter == millis(300))
        PORTB |= (1 << LED);
    else if(counter == millis(250) || counter == millis(350))
        PORTB &= ~(1 << LED);
    else if(counter == millis(2000))
        counter = 0;
}

int main(void) {

    DDRB |= (1 << LED);
    utaskConfigure();
    utaskRegister(0, ledStatus);

    set_sleep_mode(SLEEP_MODE_IDLE);
    forever() {
        sleep_mode();
    }

    return 0;
}