bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
; (b+b)-c-(a+d)  a - byte, b - word, c - double word, d - qword
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
a db 10
b dw 20
c dd 5
d dq 5
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov EAX,0
    mov AX,[b] ; AX=b
    add EAX,[b] ; EAX=b+b 
    ;cwd
    
    sub EAX,[c] ; EAX=(b+b)-c
    sub EAX,[a] ; EAX=(b+b)-c-a
    cdq ; am eliberat spatiul din EDX cu semn
    sub EAX,dword[d]
    sbb EDX,dword[d+4]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
