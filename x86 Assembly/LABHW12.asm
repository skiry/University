bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;[d-2*(a-b)+b*c]/2 a,b,c-byte d-word
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 2
    b db 1
    c db 2
    d dw 4
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov EAX,0
        mov EDX,0   
        mov AL,[a] ; AL=a
        sub AL,[b] ; AL=a-b
        mov AH,2
        mul AH ; AX=AL*AH=(a-b)*2
        mov DX,[d] ; DX=d
        sub DX,AX ; DX=DX-AX=d-2*(a-b)
        mov AX,0 ; AX=0
        mov AL,[b] ; AL=b
        mul byte[c] ; AX=AL*c=b*c
        add DX,AX ; DX=DX+AX=d-2*(a-b)+(b*c)
        mov AX,DX ; AX=DX=d-2*(a-b)+(b*c)
        mov DL,2
        div DL ; AL=AX / 2 and AH=AX % 2
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
