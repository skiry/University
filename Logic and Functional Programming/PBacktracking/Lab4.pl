%Two integers, n and m are given. Write a predicate to determine all possible sequences of numbers from 1 to n, such that between any two numbers from consecutive positions, the absolute difference to be >= m.


%                         {  [e], L is empty
%insert (l1,...,ln,e) =   {  e U (l1,...,ln)
%                         {  l1 U insert(l2,...,ln,e)

%insert(L-list, E-element integer, R-resulted list)
%flow model(i,i,o)

insert(L,E,[E|L]).
insert([H|T],E,R):-
    insert(T,E,RP),
    R = [H|RP].

%                       {  [], L is empty
%permut (l1,...,ln) =   {  insert(permut(l2,...,ln),l1), otherwise
%                       {

%permut(L-list, R-resulted list)
%flow model(i,o)

permut([],[]).
permut([H|T],R):-
    permut(T,RN),
    insert(RN,H,R).

%                    { [], e > n
%generateList(n,e) = { e U (generateList(n,e+1)), otherwise
%                    {

%generateList(N-integer,E-integer,R-resulted list)
%flow model(i,i,o)

generateList(N,E,[]):-
    E>N.
generateList(N,E,R):-
    ENew is E + 1,
    generateList(N,ENew,RP),
    R = [E|RP].

%checkHelper(L-list,E-integer,M-integer)
%flow model(i,i,i)
%checks if abs difference between any 2 consecutive elements is >= M

checkHelper([],_,_).
checkHelper([H|T],E,M):-
    E-H >= M,
    checkHelper(T,H,M).
checkHelper([H|T],E,M):-
    H-E >= M,
    checkHelper(T,H,M).

%checkList(L-list,M-integer)
%flow model(i,i)

checkList([],[]).
checkList([H|T],M):-
    checkHelper(T,H,M).

%solution(n-integer,m-integer,R-resulted list)
%flow model(i,i,o)

solution(L,M,R):-
    permut(L,RP),
    checkList(RP,M),
    R = RP.

allsol(L,M,R):-findall(RP,solution(L,M,RP),R).

main(N,M,R):-
    generateList(N,1,LST),
    allsol(LST,M,R).

