bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

;a*b-(100-c)/(b*b)+e+x
;a-word; b,c-byte; e-doubleword; x-qword

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
a dw 10
b db 2
c db 20
e dd 5
x dq 15
; our code starts here
segment code use32 class=code
    start:
        ; ...
    mov AL,[b] ; AL=b
    mov AH,0
    mov DX,0
    mul word[a] ; DX:AX=AX*a=b*a=a*b  
    push DX
    push AX
    pop EAX ; EAX=a*b
    mov EBX,EAX ; EBX=a*b   !!!
    mov CX,100 ; CX=100
    sub CX,[c] ; CX=100-c
    mov AL,[b] ; AL=b
    mul byte[b] ; AX=AL*b=b*b   
    
    mov DX,AX ; DX=b*b
    
    mov AL,CL ; AX=100-c
    mov AH,0
    mov CX,DX ; CX=b*b
    mov DX,0
    
    div CX ; AX=DX:AX/BX=(100-c)/(b*b) DX=DX:AX%BX !!!
    sub BX,AX ; BX=BX-AX=a*b-(100-c)/(b*b)
    add EBX,[e] ; EBX=EBX+e=a*b-(100-c)/(b*b)+e
    mov EAX,EBX ; mutam in eax pt a putea face urmatoarea adunare
    mov EDX,0 ; eliberam spatiul pt EDX:EAX -> qword
    add EAX,dword[x]
    add EDX,dword[x+4]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
