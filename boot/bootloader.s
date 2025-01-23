; boot/bootloader.s
BITS 16              ; We use 16-bit mode
org 0x7c00           ; The bootloader will be loaded at 0x7C00 in memory

start:
    cli              ; Disable interrupts
    xor ax, ax       ; Clear register AX
    mov ds, ax       ; Set data segment to 0

    ; Print the string "Hello, IPOOS!"
    mov si, msg      ; Load the address of the string
print_char:
    lodsb            ; Load byte from [SI] into AL
    or al, al        ; Check if the string is null-terminated
    jz done          ; If zero, end the loop
    mov ah, 0x0E     ; BIOS function: print character
    int 0x10         ; Call BIOS interrupt
    jmp print_char   ; Repeat for next character

done:
    hlt              ; Halt the CPU

msg db "IPO_OS", 0  ; Null-terminated string

times 510-($-$$) db 0 ; Fill the sector to 512 bytes
dw 0xAA55             ; Bootloader signature
