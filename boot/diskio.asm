
disk_load:

    pusha
    mov ax,dx
    
    push dx
    mov ah, 0x02
    mov al, dh
    mov cl, 0x02

    mov ch, 0x00
    mov dh, 0x00
    int 0x13
    
    je disk_error
    pop dx
    cmp al, dh
    jne sectors_error
    popa
    ret


disk_error:
    ;mov bx, MSG_DISK_ERROR
    ;call s_printString
    ;mov dh, ah
    ;;call print_hex
    jmp disk_loop

sectors_error:
    ;mov bx, MSG_SECTORS_ERROR
    ;call s_printString

disk_loop:
    jmp $

MSG_DISK_ERROR: db "Disk read error\n", 0
MSG_SECTORS_ERROR: db "Incorrect number of sectors read\n", 0
    
