%Determine the gcd of 2 numbers
%gcd(A-first number, B-second number, R-resulted integer)
%flow model(i,i,o)

%gcd(A,0,A).
%gcd(A,B,R):-NewA is mod(A,B),gcd(B,NewA).
gcd(A,B,A):-
    A=:=B.
gcd(A,B,R):-
    A>B,
    N is A-B,
    gcd(N,B,R).
gcd(A,B,R):-
    A<B,
    N is B-A,
    gcd(A,N,R).

%Determine the gcd of a list
%gcdList(L-list,R-resulted integer)
%flow model(i,o)

gcdList([R],R).
gcdList([H|T],R):-
    gcdList(T,RN),
    gcd(H,RN,R).

%Delete occurences an element E of the list that are on even positions
%delgcd(L-list,E-element to remove,CP-current position,R-resulted list)
%flow model(i,i,o)

delgcd([],_,_,[]).
delgcd([H|T],E,CP,[H|RN]):-
    H=\=E,
    NewCP is CP+1,
    delgcd(T,E,NewCP,RN).
delgcd([H|T],E,CP,[H|RN]):-
    H=:=E,
    mod(CP,2)=\=0,
    NewCP is CP+1,
    delgcd(T,E,NewCP,RN).
delgcd([H|T],E,CP,RN):-
    H=:=E,
    mod(CP,2)=:=0,
    NewCP is CP+1,
    delgcd(T,E,NewCP,RN).

%Delete the gcd of a list that occur on even positions
%main(L-list,R-resulted list)
%flow model(i,o)

main([],[]).
main(L,R):-
    gcdList(L,RN),
    delgcd(L,RN,1,R).


