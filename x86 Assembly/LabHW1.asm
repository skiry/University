bits 32 


global start        ; we need (c-a-d)+(c-b)-a where a,b,c,d-byte
                    ;        (15-5-10)+(15-8)-5=0+7-5= 2

extern exit              
import exit msvcrt.dll    


segment data use32 class=data
  
a db 5
d db 10
c db 15
b db 8

  
segment code use32 class=code
    start:
        mov AL, [c] ; AL=c
        sub AL, [a] ; AL=c-a
        sub AL, [d] ; AL=c-a-d
        mov BL, [c] ; BL=c
        sub BL, [b] ; BL=c-b
        add AL,BL ; AL=c-a-d+c-b
        sub AL,[a]
    
        ; exit(0)
        push    dword 0      
        call    [exit]       
