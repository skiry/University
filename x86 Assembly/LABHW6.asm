bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit,printf               ; tell nasm that exit exists even if we won't be defining it
import printf msvcrt.dll
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
;Se da un sir de cuvinte. Sa se construiasca doua siruri de octeti, s1 si s2, astfel: pentru fiecare cuvant,
;daca numarul de biti 1 din octetul high al cuvantului este mai mare decat numarul de biti 1 din octetul low, atunci s1 va contine octetul high, iar s2 octetul low al cuvantului
;daca numarul de biti 1 din cei doi octeti ai cuvantului sunt egali, atunci s1 va contine numarul de biti 1 din octet, iar s2 valoarea 0
;altfel, s1 va contine octetul low, iar s2 octetul high al cuvantului.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    sir dw 0x1357,0x3737,0x5713
    len equ $-sir
    s1 times len db 0
    s2 times len db 0
    bitesS1 db 0
    bitesS2 db 0
    aux dd 0
    counter db 0
    testByte db 0
    stringCounter db 0
    format1 db "s1: %x bits of 1 ",10,13,0
    format2 db "s2: %x bits of 1",10,13,0
    format db "%x ",0
; our code starts here
segment code use32 class=code

    start:
    mov ESI, sir            ; ESI = offset sir    
    cld                     ; DF = 0
    mov byte [stringCounter], 0
    mov ECX, len/2         ; ECX = 3 ( words to go through )
    main:
            mov byte [bitesS1], 0 
            mov [aux], ECX
            
            mov ECX,8 
            mov byte [counter], 1
            jmp calcS1
            afterCalcS1:
            
            mov eax,0
            mov al,[bitesS1]
            push eax
            push dword format1
            call [printf]
            add esp,4*2
            
            
            inc ESI
            
            mov ECX, 8
            mov byte [counter], 1
            mov byte [bitesS2], 0
            jmp calcS2
            afterCalcS2:
            
            mov eax,0
            mov al,[bitesS2]
            push eax
            push dword format2
            call [printf]
            add esp,4*2
            
            
            mov AL, [bitesS1]
            cmp AL, [bitesS2]
            jg S1puneLOW
            je S2pune0
            jl S1puneHIGH 
            
            continua:
                inc byte [stringCounter]
                
                mov ECX, [aux]
                dec ECX
                
                jnz main
                jz EndOf
            
    calcS1:
            LODSB
            dec ESI
            and AL, [counter] ; test bit 'counter' of byte ESI
            cmp AL, 0
            jne incrementS1 ; if !0 -> inc no of bites 1
            interiorCalcS1:
                    shl byte [counter], 1
                    dec ECX
                    jnz calcS1
                    jz afterCalcS1
                            
           
    incrementS1:
            inc byte [bitesS1]
            jmp interiorCalcS1
            
    calcS2:
            LODSB 
            dec ESI
            and AL, [counter] ; test bit 'counter' of byte ESI
            cmp AL, 0
            jne incrementS2 ; if !0 -> inc no of bites 1
            interiorCalcS2:
                    shl byte [counter], 1
                    dec ECX
                    jnz calcS2
                    jz afterCalcS2
                            
           
    incrementS2:
            inc byte [bitesS2]
            jmp interiorCalcS2
    
    S1puneLOW:
    
            mov EDI, s1
            add EDI, [stringCounter]
               
            mov eax,0
            mov al,[esi]
            mov edi,eax
            dec ESI ; ESI = the higher part of the actual word
            mov EDI, s2
            add EDI, [stringCounter]
            
            mov eax,0
            mov al,[esi]
            mov edi,eax
            add ESI, 2 ; ESI gets the right position, next word
            jmp continua
            
    S2pune0:
            mov EDI, s1
            add EDI, [stringCounter]
            mov eax,0
            mov AL, [bitesS1]
            mov edi,eax
            inc ESI
            jmp continua
      
    S1puneHIGH:
            mov EDI, s2
            add EDI, [stringCounter]
            
            mov eax,0
            mov al,[esi]
            mov edi,eax
            dec ESI ; ESI = the higher part of the actual word
            mov EDI, s1
            add EDI, [stringCounter]
            
            mov eax,0
            mov al,[esi]
            mov edi,eax
            
            add ESI, 2 ; ESI gets the right position, next word
            jmp continua
            
    EndOf:
    ;afis s1,s2!!!!!!!
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
