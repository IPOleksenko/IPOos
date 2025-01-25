#include "include/commands.h"
#include "include/terminal.h"
#include "include/io.h"

void shutdown_system() {
    terminal_writestring("Shutting down...\n");

    // Disabling through ACPI
    outw(0x604, 0x2000); // Example command for ACPI (port and data may vary)
}

void handle_command(const char* command) {
    if (!command || *command == '\0') {
        terminal_writestring("No command entered.\n");
        return;
    }

    terminal_writestring("You entered: ");
    terminal_writestring(command);
    terminal_putchar('\n');

    if (strcmp(command, "exit") == 0) {
        shutdown_system(); // Calling the shutdown function
    } else {
        terminal_writestring("Unknown command.\n");
    }
}
