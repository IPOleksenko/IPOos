#include <ctype.h>
#include <string.h>

#include <kernel/apps/handle_command.h>
#include <kernel/drv/tty.h>
#include <kernel/sys/ioports.h>
#include <kernel/sys/pit.h>
#include <kernel/sys/kheap.h>

void shutdown_system() {
    terminal_writestring("Shutting down...\n");
    sleep(1000);
    outw(0x604, 0x2000); // ACPI shutdown
}

void reboot_system(){
    terminal_writestring("Rebooting...\n");
    sleep(1000);
    outb(0x64, 0xFE);
}

extern size_t heap_used;
extern size_t heap_size;

void meminfo(){
    printf("\nRAM:\n");
    printf("Used %ld B / %ld B\n", heap_used, heap_size);
    printf("Used %ld KB / %ld KB\n", heap_used/1024, heap_size/1024);
    printf("Used %ld MB / %ld MB\n", heap_used/1024/1024, heap_size/1024/1024);
    printf("\n");
}

// Function to remove extra spaces
void trim_spaces(char* str) {
    char* dst = str;
    char* src = str;
    
    // Skip leading spaces
    while (isspace((unsigned char)*src)) src++;
    
    while (*src) {
        if (isspace((unsigned char)*src)) {
            // Replace a sequence of spaces with a single space
            *dst++ = ' ';
            while (isspace((unsigned char)*src)) src++;
        } else {
            *dst++ = *src++;
        }
    }
    
    // Removing trailing spaces
    if (dst > str && isspace((unsigned char)dst[-1])) {
        dst--;
    }
    *dst = '\0';
}

void handle_command(char* command) {
    if (!command || *command == '\0') {
        terminal_writestring("No command entered.\n");
        return;
    }

    trim_spaces(command);   

    if (strcmp(command, "help") == 0){
        terminal_writestring("Available commands:\n");
        terminal_writestring("  help     - Show this help message\n");
        terminal_writestring("  meminfo  - Displaying RAM information\n");
        terminal_writestring("  clean    - Clear the terminal screen\n");        
        terminal_writestring("  reboot   - Rebooting PC\n");
        terminal_writestring("  exit     - Exit the system\n");
    } else if (strcmp(command, "clean") == 0) {
        terminal_clear();
    } else if (strcmp(command, "reboot") == 0) {
        reboot_system();
    } else if (strcmp(command, "exit") == 0) {
        shutdown_system();
    }else if (strcmp(command, "meminfo") == 0) {
        meminfo();
    } else {
        terminal_writestring("Unknown command.\n");
    }
}