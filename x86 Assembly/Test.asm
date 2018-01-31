bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf
import printf msvcrt.dll             ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 13h,2h
    b dw -4,3,-2
    c dd 9AF8DEh
    d dw 78h, 0FFh, 0Ah
    n dw 0
    aux dd 0
    pozitiv db "Numarul e pozitiv",0
    negativ db "Numarul e negativ",0
    message db "The byte from the memory area, from the position given by the absolute value of n is: %d",0
    final times 100 db 0
    afis db "&d",0
    maska dw 0
    value db 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        mov EAX,[c]
        and EAX,0FF00h 
        mov [n],EAX
        verificare_n:
            and EAX,08000h
            mov dword [aux],EAX 
            cmp EAX,0 ;;; daca rezultatul e diferit de 0,nr e negativ, sarim la operatia de afisare 
            jne afiseazaNeg
            cmp dword [aux],0 ;; daca e pozitiv, sarim la cealalta op de afisare
            je afiseazaPoz
        afiseazaNeg:
            push dword negativ
            call [printf]
            add ESP,4 ; afisam negativ, sarim la functia cont, pentru a sari peste afisarea de nr poztitiv
            jmp cont
        afiseazaPoz:
            push dword pozitiv
            call [printf]
            add ESP,4  
            jmp cont
        cont:  
            mov EAX,dword [n]
            mov word [maska],AX
            sar word[maska],15 ;;; facem o masca de 15 biti cu 1 pt nr neg,resp 0 pt nr poz
            mov EAX,0
            mov AX,word [maska]
            add AX,word[n] ; adunam masca cu n
            xor AX,[maska] ; facem xor pe masca si suma dintre masca si n=> modul n
            mov word[n],AX ; in n avem modul n => n=abs(n)
            
            mov ESI,a
            push dword [ESI+n]; m am gandit sa pun offsetul din var A in ESI=> cand trece de a, trece la urmatoarele variabile de dupa a
            push dword message 
            call [printf]
            add ESP,4*2 ; deci asta afiseaza ESI+n, byteul cu indexul n din memorie
            
        mov DL,0
        mov byte[value],DL  ; am pus value=0
        mov ECX,dword[n] ; ECX=n
        do:
            mov EDX, dword[value]     ;rulam DO de n/2 ori, deoarece decrementam ECX la sfarsit inca o data
            mov dword[final],EDX ; punem in EDX value, apoi in vectorul final EDX
            inc byte[value]
            dec ECX
        loop do
        mov ECX,dword[value]
        afis_final:
            PUSHAD
            push dword[final] ; afisam final
            push dword afis
            call [printf]
            add ESP,4*2
            POPAD
            dec byte[value]
        loop afis_final
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
