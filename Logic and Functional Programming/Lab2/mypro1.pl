%Insert an element E on a position P in a list L
%ins (L-list, E-elem - integer,
      %IP-insert position - integer,
      %CP-current position - integer,
      %RL-resulted list)
%flow model: (i,i,i,i,o)

ins([],E,_,1,[E]).
ins([],_,_,_,[]).
ins(L,E,IP,CP,R):-CP=:=IP,
                 NewCP is CP+1,
                 ins(L,E,IP,NewCP,RT),
                 R=[E|RT].
ins([H|T],E,IP,CP,R):-NewCP is CP+1,
                     ins(T,E,IP,NewCP,RT),
                     R=[H|RT].
