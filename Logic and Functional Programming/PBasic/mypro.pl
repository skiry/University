%product of even numbers from a list
%mypro(L-list, R-result, integer)
%flow model(i,o) - the result will be computed
%flow model(i,i) - the result will be checked

mypro([],1).
mypro([H|T],R):-mod(H,2)=:=0,
    mypro(T,RT),
    R is RT*H.
mypro([H|T],R):-mod(H,2)=\=0,
    mypro(T,RT),
    R is RT.

%call the predicate
%mypro([1,2,4,10,12],R).
%or
%mypro([1,2,4,10,12],960).
