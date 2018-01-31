bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;(e+f)*g e,f,g-word
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
e dw 1
f dw 2
g dw 3
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov AX,[e] ; AX=e
        add AX,[f] ; AX=e+f
        mul word[g] ; DX:AX=AX*g
        push DX
        push AX
        pop EAX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
