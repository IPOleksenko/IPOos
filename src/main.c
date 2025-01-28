#include "include/main.h"

#include "include/keyboard.h"
#include "include/handle_command.h"

void main(void){
    while (1) {
            handle_command(keyboard_input());
        }
}
