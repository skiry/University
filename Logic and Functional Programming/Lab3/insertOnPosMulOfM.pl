%Insert an element E on all position multiple of M
% insertOnM(L-list, E-elem to be inserted, CP-current position, M-which
% positions, R-resulted list)
% flow model(i,i,i,i,o)

insertOnM([],_,_,_,[]).
insertOnM([],E,CP,M,[E]):-
    mod(CP,M)=:=0.
insertOnM(L,E,CP,M,R):-
    mod(CP,M)=:=0,
    NewCP is CP+1,
    insertOnM(L,E,NewCP,M,NR),
    R=[E|NR].
insertOnM([H|T],E,CP,M,R):-
    mod(CP,M)=\=0,
    NewCP is CP+1,
    insertOnM(T,E,NewCP,M,NR),
    R=[H|NR].
