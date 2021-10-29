/* Motoristas(nome, disponibilidade{0-Nao, 1-Sim}, X, Y)
    X,Y - sendo a localizacao
*/

motorista(carlos, 0, 5, 3).
motorista(bruno, 1, 10, 10).
motorista(ares, 0, 9, 15).
motorista(artemis , 1, 28, 50).
motorista(afrodite, 0, 31, 21).
motorista(eros, 1, 27, 15).
motorista(hades, 0, 10, 3).
motorista(ashura, 1, 7, 5).
motorista(yamashiro, 0, 100, 100).
motorista(ageha, 1, 23, 49).
motorista(uchiha, 0, 93, 43).
motorista(atlas, 1, 79, 31).

/* Cliente(nome, X, Y) 
    X,Y - sendo a localizacao
*/

cliente(hiperion, 85, 35).
cliente(perseu, 90, 80).
cliente(teseu, 0, 15).
cliente(ceryx, 15, 15).
cliente(deimos, 42, 12).
cliente(erinias, 9, 3).
cliente(euriale, 10, 3).
cliente(icarus, 100, 100).
cliente(lanaeus, 78, 2).
cliente(thera, 26, 41).
cliente(dean, 36, 85).
cliente(daen, 5, 7).
cliente(jake, 25, 62).

/* Funcoes */
minimo(X,Y,Y) :- X >= Y, !.
minimo(X,Y,X) :- X < Y.

distancia(Xa,Ya, Xb, Yb, D) :- D is ((Xb-Xa)**2 + (Yb-Ya)**2)**(1/2).


/*
Generico:
cliente(Cliente,Y,Z), motorista(Motorista, 1, K, L), distancia(Y,Z,K,L,Distancia).

Cliente fixo:
cliente(daen,Y,Z), motorista(Motorista, 1, K, L), distancia(Y,Z,K,L,Distancia).

findall(C, (cliente(daen,Y,Z), motorista(Motorista, 1, K, L), distancia(Y,Z,K,L,C)), L), min_list(L,Min), indexOf(L,Min,Indice).
L = [lista].
Min = 2.8284271247461903,
Indice = 3.
*/
min_list([H|T], Min) :-
    min_list(T, H, Min).

min_list([], Min, Min).
min_list([H|T], Min0, Min) :-
    Min1 is min(H, Min0),
    min_list(T, Min1, Min).

indexOf([Element|_],Element,0):-!.
indexOf([_|Tail],Element,Index):-
	indexOf(Tail,Element,Index1),
	Index is Index1 + 1.

match([H|_],0,H) :-
    !.
match([_|T],N,H) :-
    N > 0, %add for loop prevention
    N1 is N-1,
    match(T,N1,H).

match([Elem|Tail],Num,Counter,MatchedNumber):-
    match(Tail,Num,N,Elem),
    C is N+1.

encontraeElem(0, [H|_], H):- !.
encontraeElem(I, [_|T], E):- X is I - 1, encontraeElem(X, T, E).

/*
A menor distancia

findall(C, (cliente(daen,Y,Z), motorista(Motorista, 1, K, L), distancia(Y,Z,K,L,C)), L),
             min_list(L,Min), 
             indexOf(L,Min,Indice).

findall(C, (cliente(daen,Y,Z), motorista(C, 1, K, L), distancia(Y,Z,K,L,Distancia)), Mtrs), 
findall(C, (cliente(daen,Y,Z), motorista(Motorista, 1, K, L), distancia(Y,Z,K,L,C)), L),
min_list(L,Min), 
indexOf(L,Min,Indice),
encontraeElem(Indice, Mtrs, MotoristaSolicitado).

*/