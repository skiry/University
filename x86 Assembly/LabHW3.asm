bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
;Se dau octetii A si B. Sa se obtina dublucuvantul C:
;   bitii 0-3 ai lui C coincid cu bitii 3-6 ai lui B
;   bitii 4-7 ai lui C au valoarea 0
;   bitii 8-10 ai lui C au valoarea 110
;   bitii 11-15 ai lui C coincid cu bitii 0-4 ai lui A
;   bitii 16-31 ai lui C sunt 1
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
A db 8
B db 3
C dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov EAX, 0 ; EAX va fi C
    mov BL,byte[B] ; BL=3
    shr BL,3 ; shiftam la dreapta cu 3 poz
    and BL,0Fh ; aplicam & pe 00001111
    mov AL,BL 
    mov AH,6 ; 8-10 au bitii 110
    shl byte[A],3 ; shiftam la stanga cu 3 poz
    or AH,byte[A] ; mutam primii 5 biti din A in AH
    or EAX,0FFFF0000h ; setam 1 pe poz 16-31
    mov [C],EAX
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
