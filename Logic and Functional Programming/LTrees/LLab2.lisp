;Return the number of levels (depth) of a tree of type 1
;#3
;                            { 
;getDepth(L, currentDepth) = { getDepth( (CDR L), currentDepth + 1 ) , (CAR L) = node (atom and not number) AND its number of children != 0
;     A
;   B   D     (A 2 B 1 Z 1 C 0 D 2 E 0 F 0)
;    Z E F
;   C


(DEFUN getDepth (l curD)
  ( COND
 ( (NULL l) NIL)
 ( (AND (NULL (stang(subarbori (cddr l) 0 0))) (NULL (drept(subarbori (cddr l) 0 0)))) curD)
 ( (NULL (drept(subarbori (cddr l) 0 0))) (getDepth (stang(subarbori (cddr l) 0 0)) (+ 1 curD)))
 ( T (MAX (getDepth (stang(subarbori (cddr l) 0 0)) (+ 1 curD) ) (getDepth (drept(subarbori (cddr l) 0 0)) (+ 1 curD) )))
 )
 )

 ;; Return the level (depth) of a node in a tree of type (1). The level of the root element is 0.

 (DEFUN subarbori ( l n m )
 (cond
 ((null l) nil)
 ((eq n (+ 1 m)) (list l))
 (t (append (append (list (car l)) (list(cadr l)))(subarbori (cddr l) (+ 1 n) (+ m (cadr l))) ) )
 )
 )
 
 (defun depth (l a r)
 (cond
 ((null l) nil)
 ((eq (car l) a) r)
 ((not (null (member a (drept(subarbori (cddr l) 0 0)))))(depth (drept(subarbori (cddr l) 0 0)) a (+ 1 r)))
 (t(depth (stang(subarbori (cddr l) 0 0)) a (+ 1 r)))
 )
 )
 

 (defun stang (l)
 (cond
 ((null l) nil)
 ((atom (car l)) (cons (car l) (stang (cdr l))))
 )
 )
 
 (defun drept(l)
(cond
((null l ) nil)
((listp (car l)) (car l))
(t (drept (cdr l)))
 ))
 
;apel:  (write (depth '(A 2 B 0 C 2 D 0 E 0) 'E 0))
; se va afisa 2

;Return the list of nodes of a tree of type 2 accesed inorder.
;#8
;inorder(L) = { APPEND( CDR, CAR, CDDR )

(DEFUN left-tree (L)
 ( COND
  ( (NULL L) NIL )
  ( (NOT (LISTP L)) NIL )
  ( T (CADR L) )
 )
)

(DEFUN right-tree (L)
 ( COND
  ( (NULL L) NIL )
  ( (NOT (LISTP L)) NIL )
  ( T (CADDR L) )
 )
)

( DEFUN inorder2 (L)
 ( COND 
  ( (NULL L) NIL )
  ( T ( APPEND (inorder2 (left-tree L)) (LIST (CAR L)) (inorder2 (right-tree L)) ) ) 
 )
)

;Return the path from the root to a given node, type 1
;#1

( DEFUN path (L Node)
  ( COND
    ( (NULL L) NIL )
    ( (NOT (NULL (MEMBER Node ( drept ( subarbori (CDDR L) 0 0 ))))) (APPEND (LIST (CAR L)) (path (drept (subarbori (CDDR L) 0 0) ) Node)))
    ( T (APPEND (LIST (CAR L)) (path (stang (subarbori (CDDR L) 0 0) ) Node)))
  )
)

;The list of nodes in preorder, type 1
;#14

( DEFUN preorder1 (L)
  ( COND
    ( (NULL L) NIL )
    ( T ( APPEND (LIST (CAR L)) (preorder1 (stang(subarbori (CDDR L) 0 0))) (preorder1 (drept(subarbori (CDDR L) 0 0)))))
  )
)