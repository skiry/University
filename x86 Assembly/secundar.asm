 bits 32 

global secundar    

; declare external functions needed by our program
extern exit, printf
import exit msvcrt.dll 
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
; our code starts here
segment code use32 class=code
    secundar:
       mov edi, [esp+4]
       mov eax,0
       mov al, [esp+8]
       mov ecx, eax
       bucla:
        inc edi
       loop bucla
       cmp [edi],'a'
       je unu
       cmp [edi],'e'
       je unu
       cmp [edi],'i'
       je unu
       cmp [edi],'o'
       je unu
       cmp [edi],'u'
       je unu
       mov eax,0
       ret eax
       unu:
       mov eax,1
       ret eax
        ; exit(0)
        push    dword 0      
        call    [exit]       
