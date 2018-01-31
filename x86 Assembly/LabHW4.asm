bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

;Se dau doua numere naturale a si b (a, b: word, definite in segmentul de date). 
;Sa se calculeze a/b si sa se afiseze catul si restul impartirii in urmatorul format:
;"Cat = <cat>, rest = <rest>"
;Exemplu: pentru a=23 si b=10 se va afisa: "Cat = 2, rest = 3"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.

; declare external functions needed by our program
extern exit,printf             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll               ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
a dw 23
b dw -10
cat db "cat = %d",0
restul db "rest = %d",0
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov EAX,0
    mov EDX,0
    mov AX,[a] ; AX=a -> AX=23
    cwd ; DX=0 se pregateste pt impartire cu semn
    idiv word [b] ; AX=DX:AX/[b] DX=DX:AX%[b]
    PUSHAD ; pt a pastra valorile in EDX ulterior 
    cwde
    push EAX
    push cat
    call [printf]
    add ESP, 4*2
    POPAD ; pt a afisa EDX corect mai jos
    PUSHAD
    mov AX, DX
    cwde
    push EAX
    push restul
    call [printf]
    add ESP,4*2
    POPAD
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
