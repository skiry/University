% Se dau doua liste A si B.
% a) Sa se determine valorile elementelor maxime din cele doua liste. b)
% Sa se creeze o lista noua N care va contine valorile maxime obtinute
% dublate
% A = [4, 7, 2, 6]
% B= [11, 10, 9]
% a) Max_a = 7 Max_b = 11 b) NL = [ 14, 22 ]

%Get the maximum from a list
%getMax(L-list, R-resulted integer)
%flow model(i,o)

getMax([],-9999999999).
getMax([H],H).
getMax([H|T],H):-
    getMax(T,MaxTail),
    H>MaxTail.
getMax([H|T],R):-
    getMax(T,MaxTail),
    H=<MaxTail,
    R is MaxTail.
%                           {  [], l = []
%                           {  l1, l has 1 element
%getMax(l1,l2,...,ln,MAX) = {  getMax(l2,...,ln,l1), HEAD > MAX
%                           {  getMax(l2,...,ln,MAX), OTHERWISE

%Create a new list with those elements, doubled
%createNew(A-first element, B-second element, NL-resulted list)
%flow model(i,i,o)

createNew(A,B,NL):-
    NewA is A*2,
    NewB is B*2,
    NL = [NewA,NewB].

%Main function gets 2 lists and returns the new list
%main(L1-list, L2-list, NL-resulted list)
%flow model(i,i,o)

main(L1,L2,NL):-
    getMax(L1,L1max),
    getMax(L2,L2max),
    createNew(L1max,L2max,NL).
