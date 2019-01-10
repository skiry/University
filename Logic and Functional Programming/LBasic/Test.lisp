(DEFUN linearization (L)
  (COND
   ((NULL L) NIL)
   ((NUMBERP L) (LIST L))
   ((LISTP L)(apply 'append (mapcar 'linearization L)))
  )
) 

; revNumerical (l1,...,ln) = { l1 U revNumerical(l2,...,ln), l1 unique
;                            { revNumerical(l2,...,ln), otherwise
(DEFUN revNumerical (L)
  (COND
   ((NULL L) NIL)
   ((NOT (NULL (MEMBER (CAR L) (CDR L)))) (revNumerical (CDR L)))
   (T (CONS (CAR L) (revNumerical (CDR L))))
  )
)

(DEFUN main (L)
  (REVERSE (revNumerical (linearization L)))
)