readKey:
  push ax
  mov ah, 0x00
  int 0x16
  pop ax
  ret
