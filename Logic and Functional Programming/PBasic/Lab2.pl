%Remove all occurences of an atom E from a list L
%removeOcc (L-list, E-elem - integer, RL-resulted list)
%flow model(i,i,o)

removeOcc([],_,[]).
removeOcc([H|T],E,RL):-
    H=\=E,
    removeOcc(T,E,NL),
    RL=[H|NL].
removeOcc([H|T],E,RL):-
    H=:=E,
    removeOcc(T,E,NL),
    RL=NL.


%                          { [],if list is empty
%removeOcc(l1,l2,..,ln,E) ={ removeOcc(l2,..,ln),l1!=E
%                          { removeOcc(l2,..,ln) U l1, otherwise


%Count number of occurences of an atom
%count (L-list, E-elem - integer, nr-result)
%flow model(i,i,o)

count([],_,0).
count([H|T],E,NR):-
    H=:=E,
    count(T,E,NewNr),
    NR is NewNr+1.
count([H|T],E,NR):-
    H=\=E,
    count(T,E,NewNr),
    NR is NewNr.
%                     { 0,if list is empty
% count(l1,..,l2,E) = { 1+count(l2,..,ln,E),l1=E
%                     { count(l2,..,ln,E),otherwise


%Produce a list of atom-nrOfOccurences
%makeList (L-list, RL-resulted list)
%flow model(i,o)
%
makeList([],[]).
makeList([H|T],RL):-
    count([H|T],H,NR),
    removeOcc([H|T],H,RLL),
    makeList(RLL,NL),
    NNL=[H,NR],
    RL=[NNL|NL].

%                     { [],if the list is empty
%makeList(l1,..,ln) = { makeList(removeOcc(l1,..,ln),NL), otherwise
