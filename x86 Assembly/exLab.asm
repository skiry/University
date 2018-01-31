@mail+secundar.asm
bits 32 

global start        

; declare external functions needed by our program
extern exit, printf, scanf, secundar
import exit msvcrt.dll  
import printf msvcrt.dll
import scanf msvcrt.dll
import secundar 
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    S db "Iau 10 la lab",0
    N dd 0
    format db "%d",0
    afis db "Daca e vocala, se afiseaza 1, altfel, 0, %d",0
; our code starts here
segment code use32 class=code
    start:
       push dword N
       push dword format
       call [scanf]
       add esp,4*2

       push dword [N]
       push dword S
       call secundar
       
       
           push eax
           push afis
           call [printf]
           add esp,4*2
      
        
        ; exit(0)
        push    dword 0      
        call    [exit]       
        
        
