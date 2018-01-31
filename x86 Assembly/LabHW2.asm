bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
                            ;(a-b)+(c-b-d)+d ;  a - byte, b - word, c - double word, d - qword -> rez=20
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
a db 10
b dw 5
c dd 20
d dq 15
; our code starts here
segment code use32 class=codew
    start:
        ; ...
    mov EAX,0
    mov AL,[a] ; AL=a   a byte
    sub AX,[b] ; AX=a-b     b word-> scad din AX
    mov EDX,[c] ; EDX=c   c dword-> am nevoie de EDX
    sub EDX,[b] ; EDX=c-b    
    sub EDX,[d] ; EDX=c-b-d
    add EAX,EDX ; EAX=(a-b)+(c-b-d)  
    add EAX,[d] ; EAX=(a-b)+(c-b-d)+d
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
