;Function that produces the linear list of all atoms from all levels written in the same order!
;#16

( DEFUN linearization (L)
 ( COND
  ( ( NULL L ) NIL )
  ( ( ATOM L ) (LIST L) )
  ( T (apply #' append (mapcar 'linearization L) ) )
 )
)

;Sum of even numbers - odd numbers
;#5

( DEFUN sum (L)
 ( COND
  ( (NULL L) NIL )
  ( (AND (NUMBERP L) (EQUAL (MOD L 2) 0)) L)
  ( (AND (NUMBERP L) (EQUAL (MOD L 2) 1)) (- 0 L))
  ( (ATOM L) 0)
  ( T (apply '+ (mapcar 'sum L)))
 )
)

;Check if an atom is a member of a non-linear list
;#1

( DEFUN check (L el)
  ( COND 
    ( (NULL L) NIL )
    ( (equal L el) T )
    ( (LISTP L) (apply 'append (mapcar (lambda(x) (check x el)) L ) ))
  )
)

( DEFUN check2 (L el)
  ( COND
    ( (NULL L) NIL )
    ( (AND (LISTP L) (not (equal NIL (MEMBER el L))) T ))
    ( (LISTP L) (apply 'append (mapcar (lambda(x) (check2 x el)) L) ))
  )
)

;The sum of numeric atoms at any level
;#2

( DEFUN sumNumericHelper (L)
  ( COND
    ( (NULL L) NIL )
    ( (NUMBERP L) (LIST L) )
    ( (LISTP L) (apply 'append (mapcar 'sumNumericHelper L)))
  )
)

( DEFUN sumNumeric (L)
  (apply '+ (sumNumericHelper L))
)

;Substitute an atom with another one at any level
;#12

( DEFUN replaceAtom (L old new)
  ( COND
    ( (NULL L) NIL )
    ( (AND (ATOM L) (NOT (EQUAL L old))) L )
    ( (equal L old) new )
    ( (LISTP L) (mapcar (lambda(x) (replaceAtom x old new)) L))
  )
)