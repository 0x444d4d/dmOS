
[org 0x7c00]
KERNEL_OFFSET equ 0x1000

  mov [BOOT_DRIVE], dl
  mov bp, 0x9000
  mov sp, bp

  ;mov bx, msg_real_mode
  ;call s_printString

  call loadKernel
  call switch
  jmp $

%include "./boot/screenout.asm"
%include "./boot/diskio.asm"
%include "./boot/keyboard.asm"
%include "./boot/32b-gdt.asm"
%include "./boot/32b-print.asm"
%include "./boot/32b-switch.asm"

[bits 16]
loadKernel:
  ;mov bx, msg_loading_kernel
  ;call s_printString

  mov bx, KERNEL_OFFSET
  mov dh, 52
  mov dl, [BOOT_DRIVE]
  call disk_load


  ;mov bx, msg_kernel_loaded
  ;call s_printString
  ret
  
[bits 32]
BEGIN_PM:
  mov ebx, msg_protected_mode
  call print_string_pm
  call KERNEL_OFFSET
  jmp $

BOOT_DRIVE db 0
msg_real_mode db "Real mode\n", 0
msg_protected_mode db "Protected mode", 0
msg_loading_kernel db "Cargando kernel\n", 0
msg_kernel_loaded db "Kernel cargado\n", 0


times 510 - ($-$$) db 0
dw 0xaa55

