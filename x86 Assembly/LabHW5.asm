bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

;;;Se dau doua siruri de octeti S1 si S2 de aceeasi lungime. Sa se obtina sirul D prin intercalarea elementelor celor doua siruri. 
;Exemplu:

;S1: 1, 3, 5, 7
;S2: 2, 6, 9, 4
;D: 1, 2, 3, 6, 5, 9, 7, 4

; declare external functions needed by our program
extern exit, printf              ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll  ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    S1 db 1,3,5,7
    S2 db 2,6,9,4
    D times 8 db 0 ; the final vector will contain 8 elements
    print db "%d, ",0 ; printing the final vector
; our code starts here
segment code use32 class=code
    start:
        ; ...
       mov ecx,4 ; go through the vectors S1 and S2 of length 4
       mov esi,0 ; we will iterate over the positions of ESI : 0,1,2,3
       solveProb:
            mov al,[S1+esi]      ; we put the element indexed with ESI of S1 in D
            mov [D+esi*2],al
            mov al,[S2+esi]      ; we put the element indexed with ESI of S2 in D
            mov [D+esi*2+1],al
            inc esi            ; increment ESI
       loop solveProb ; LOOP WHILE ECX != 0 -> iterate 4 times
       mov ecx,8 ; NOW WE WANT TO ITERATE 8 TIMES
       mov esi,0
       printList:
            mov eax,0
            mov al,[D+esi]
            
            PUSHAD
            push eax
            push dword print ; PRINT THE D LIST
            call [printf]
            add esp,4*2
            POPAD
            
            inc esi
       loop printList ; LOOP PRINTLIST 8 TIMES
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
