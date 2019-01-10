; Write a function that inserts in a linear list after even positions an atom A

; insert(l1, ..., ln, b, count) = { l1 U b U insert(l2, ..., ln, b, 1 - count), count = 1
;                                 { l1 U insert(l2, ..., ln, b, 1 - count), otherwise

( DEFUN insertHelper(L A count)
  ( COND
    ( (NULL L) NIL )                   ;; instead of CONS ( CONS ) with output ( 1 2 (3 . 4) ) 
                                       ;; use APPEND ( LIST ) to have ( 1 2 3 4)
    ( ( = count 1 ) ( APPEND ( LIST (CAR L) A  ) ( insertHelper (CDR L) A (- 1 count) ) ) )
    ( T ( CONS (CAR L) (insertHelper (CDR L) A (- 1 count) ) ) )
  )
)

( DEFUN insert(L A)
  ( insertHelper L A 0 )
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

; Write a function to get from a given list the list of all atoms on any level, but reverse order
; Ex: ((A) (B (C D)) E) => (E D C B A)

;               { NIL, L is empty
; getAtoms(L) = { getAtoms(L1) U getAtoms(L2,..,Ln), L1 is a list
;               { L1 U getAtoms(L2,..,Ln), L1 is an atom
;               { L1, otherwise

( DEFUN getAtoms(L)
  ( COND
    ( (NULL L) NIL )
    ( ( LISTP (CAR L) ) ( APPEND ( getAtoms (CAR L) ) ( getAtoms (CDR L) ) ) )
    ( ( ATOM (CAR L) ) ( CONS (CAR L) (getAtoms (CDR L)) ) )
    ( T (getAtoms (CDR L)) )
  )
)

( DEFUN getReversedAtoms(L)
  ( REVERSE (getAtoms L) )
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Write a function that returns the greatest common divisor of all numbers in a nonlinear list

; gcd(a, b) = { gcd(b, a%b), b != 0
;             { a, otherwise

( DEFUN mygcd(a b)
  ( COND 
    ( (= b 0) a )
    ( T ( mygcd b (MOD a b) ) )
  )
)

( DEFUN liniarization(L)
  ( COND
    ( (NULL L) NIL)
    ( ( LISTP (CAR L) ) ( APPEND ( liniarization (CAR L) ) ( liniarization (CDR L) ) ) )
    ( ( NUMBERP (CAR L) ) ( CONS (CAR L) ( liniarization (CDR L) ) ) )
    ( T ( liniarization (CDR L) ) )
  )
)

; gcdList(L) = { L1, CDR L is null
;              { gcd(CAR L, gcdList(CDR L) ), otherwise

( DEFUN gcdList(L)
  ( COND
    ( ( equal (CDR L) NIL) (CAR L) )
    ( T ( gcd (CAR L) ( gcdList (CDR L) ) ) )
  )
)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;Write a function that determines the number of occurences of an atom in a nonlinear list

;                   { countAtom(CAR L) + countAtom(CDR L), CAR L is list
; countAtom(L, A) = { 1 + countAtom(CDR L), CAR L is atom = A
;                   { countAtom(CDR L), otherwise

( DEFUN countAtom(L A)
  ( COND
    ( (NULL L) 0 )
    ( ( LISTP (CAR L) ) (+ ( countAtom (CAR L) A ) ( countAtom (CDR L) A ) ) )
    ( ( and (ATOM (CAR L)) (equal (CAR L) A) ) (+ 1 (countAtom (CDR L) A) ) )
    ( T ( countAtom (CDR L) A ) )
  )   
)

;----------------------------------------------------------------------------------------
;Cmmmc of the numerical values of a nonlinear list
;#11a

(DEFUN linNr (L)
  (COND
    ((NULL L) NIL )
    ((NUMBERP L) (LIST L) )
    ((LISTP L) (apply 'append (mapcar 'linNr L)))
  )
)

(DEFUN cmmmcNr (a b)
  (COND
   ((EQUAL b 0) a)
   (T (cmmmcNr b (MOD a b)))
  )
)

(DEFUN cmmmcHelper (L)
  ( COND
    ((EQUAL (LENGTH L) 1) (CAR L))
    (T (cmmmcNr (CAR L) (cmmmcHelper (CDR L))))
  )
)

(DEFUN cmmmc (L)
  (cmmmcHelper (linNr L))
) 

;The product of numerical even atoms at any level
;#11d

(DEFUN evenProdHelper (L)
  ( cond
    ((NULL L) NIL)
    ((AND (NUMBERP L) (EQUAL (MOD L 2) 0)) (LIST L))
    ((LISTP L) (apply 'append (mapcar 'evenProdHelper L)))
  )
)

(DEFUN evenProd (L)
  (apply '* (evenProdHelper L))
)

;Remove all occurrences of a maximum numerical element from a nonlinear list
;11c

(DEFUN getMax (L)
  (COND
   ((NULL L) -99999999999)
   ((AND (ATOM L) (NOT (NUMBERP L))) -999999999999)
   ((NUMBERP L) L)
   ((LISTP L) (apply 'MAX (mapcar 'getMax L)))
  )
)

(DEFUN delMax (L)
  (CAR (remEl L (getMax L)))
)

(DEFUN remEl (L el)
  (COND 
   ((NULL L) NIL)
   ((EQUAL L el) NIL)
   ((ATOM L) (LIST L))
   ((LISTP L) (LIST (apply 'append (mapcar (lambda(x)(remEl x el)) L))))
  )
)

;Check if a linear list has a 'mountain' aspect. At least 3 elements
;11b

(DEFUN mountainHelper (L direction)
  (COND
   ((NULL L) T)
   ((AND (NULL (CDR L)) (EQUAL direction 1)) NIL)
   ((AND (NOT(NULL (CDR L)))(AND (< (CADR L) (CAR L)) (EQUAL direction 1))) (mountainHelper (CDR L) (- 1 direction)))
   ((AND (NOT(NULL (CDR L)))(AND (> (CADR L) (CAR L)) (EQUAL direction 0))) NIL)
   (T (mountainHelper (CDR L) direction))
  )
)

(DEFUN mountain (L)
  (COND
   ((< (CADR L) (CAR L)) NIL)
   (T (mountainHelper L 1))
  )
)