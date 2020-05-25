    
    global sse_imagen_a_blanco_y_negro
    
    section .text
    
    ;RCX(ptr_imagen), RDX(ancho), R8(alto), r10(umbral)
    
sse_imagen_a_blanco_y_negro:
    xor rax, rax
    
    test rcx, rcx
    jz fin
    test rcx, 16
    jz fin
    
    imul edx, r8d             ; ancho por alto
    mov eax, edx
    shr eax, 4
    
    mov r10d, eax             ; contador de bloques
    cmp eax, 0
    jz menos_16_pixeles
    
    movd xmm1, r10d           ; cargamos el umbral
    pxor xmm0, xmm0           ; ponemos a cero el xmm0
    pshufb xmm1, xmm0         ; inicializamos 16 bytes con el valor umbral
bucle:
    movdqa xmm0, [rcx]        ; cargamos un dato
    pminub xmm0, xmm1         ; si dato > umbral, almacenamos el umbral
    pcmpeqb xmm0, xmm1
    movdqa [rcx], xmm0
    add rcx, 16
    dec r10d
    jnz bucle
    
menos_16_pixeles:
    and edx, 0xf
    jz fin
    
bucle2:
    mov esi, 255
    mov al, [rdx]
    add al, cl
    jnz bucle2
    
    mov rax, 1
fin:
    ret
    
    
    
