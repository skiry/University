%Replace all occurrences of an element from a list with another element e.
%replaceOcc(L-list, this-integer, e-integer, RL-resulted List)
%flow model(i,i,i,o)

replaceOcc([],_,_,[]).
replaceOcc([H|T], This, E, RL):-
    H=:=This,
    replaceOcc(T, This, E, R),
    RL=[E|R].
replaceOcc([H|T], This, E, RL):-
    H=\=This,
    replaceOcc(T, This, E, R),
    RL=[H|R].
%                                 { [],if list is empty
%replaceOcc(l1,l2,..,ln,This,E) = { replaceOcc(l2,..,ln) U E,l1 == E
%                                 { replaceOcc(l2,..,ln) U l1, otherwise


%Get the maximum from a list.
%getMax(L-list, Max-resulted integer)
%flow model(i,o)

getMax([],-inf).
getMax([H],-inf):-
    is_list(H).
getMax([H],-inf):-
    atom(H).
getMax([H],H):-number(H).
getMax([H|T],H):-
    number(H),
    getMax(T,RN),
    H>RN.
getMax([H|T],RN):-
    number(H),
    getMax(T,RN),
    H=<RN.
getMax([H|T],RN):-
    atom(H),
    getMax(T,RN).
getMax([H|T],RN):-
    is_list(H),
    getMax(T,RN).



%                        { [],if list is empty
%getMax(l1,l2,..,ln,R) = { getMax(l2,..,ln,NR), R=l1,l1 > NR
%                        { getMax(l2,..,ln,NR), R=NR, otherwise

% For a heterogeneous list, formed from integer numbers and lists of
% numbers and replace the maximum value of the list in each sublist with
% the maximum value of sublist.

%replaceSubMax(L-list, RL-resulted list)
%flow model(i,o)

%helper(L-list, V-maximum from the list, RL-resulted list)
%flow model(i,i,o)

replaceSubMax([],[]).
replaceSubMax(L,RL):-
    getMax(L,Here),
    helper(L,Here,RL).

helper([],_,[]).
helper([H|T],V,RL):-
    is_list(H),
    getMax(H,AltMax),
    replaceOcc(H,V,AltMax,RS),
    helper(T,V,RN),
    RL=[RS|RN].
helper([H|T],V,RL):-
    helper(T,V,RN),
    RL=[H|RN].

%                        { [],if list is empty
%helper(l1,l2,..,ln,V) = { helper(l2,..,ln,V) U V,l1 == V
%                        { helper(l2,..,ln,V) U l1, otherwise
