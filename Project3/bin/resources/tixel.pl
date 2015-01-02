
/******************************************************************************
*******************************************************************************
*******                                                                 *******
*******                      =====   TIXEL 2   =====                    *******
*******                                                                 *******
*******  Tixel 2 is a board game created by Nestorgames.                *******
*******                                                                 *******
*******  Game rules: http://www.nestorgames.com/rulebooks/TIXEL_EN.pdf  ******* 
*******                                                                 *******
*******                                                                 *******
*******                                                                 *******
*******************************************************************************
*******************************************************************************/





:-use_module(library(sockets)).
:-use_module(library(system)).
:-use_module(library(between)).
:-use_module(library(lists)).







/******************************************************************************
*******************************************************************************
******************                                           ******************
******************    AUXILIAR GENERAL PUPOSE PREDICATES     ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

minor(X,Y,X):- X < Y, !.
minor(_,Y,Y).

kversor(A1,A2,B1,B2,K):- 
		K is (A1*B2)-(A2*B1).

oneof2iszero(0,_).
oneof2iszero(_,0).

unidelta(Delta,1):- Delta > 0, !.
unidelta(Delta,-1):- Delta < 0, !.
unidelta(0,0).

different_cells([I1,_],[I2,_]):- I1 =\= I2.
different_cells([_,J1],[_,J2]):- J1 =\= J2.

list_select([H|_],0,H).
list_select([_|T],J,Ret):- 	J1 is J-1, J > 0, 
		!, list_select(T,J1,Ret).

list_update(List,J,C,NewList) :- 
		gameboard_linecell_update(List,J,C,0,NewList).
list2_swap([X,Y],[Y,X]).


toggle(0,1).
toggle(1,0).


not(X):- X, !, fail.
not(_).











/******************************************************************************
*******************************************************************************
******************                                           ******************
******************        AUXILIAR INTERFACE PREDICATES      ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

clean_page:-
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,
		nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl,nl.

character(0):-put_code(9617). /* light gray block*/
character(1):-put_code(9618). /* gray block */
character(2):-put_code(9619). /* dark gray block */
character(3):-put_code(9608). /* black block */ 
character(4):-put_code(8193). /** full with space **/
					
pinta_n_chars(_,0).
pinta_n_chars(Char,N) :- 
		character(Char), 
		N1 is N-1, 
		!, pinta_n_chars(Char,N1).

bg(_,J,NChars):- J < 0, 
		pinta_n_chars(4,NChars).
bg(I,_,NChars):- I < 0, 
		pinta_n_chars(4,NChars).
bg(I,J,NChars):- J >= 0, I >= 0, 0 is (I+J) mod 2, 
		pinta_n_chars(0,NChars).					
bg(I,J,NChars):- J >= 0, I >= 0, 1 is (I+J) mod 2, 
		pinta_n_chars(1,NChars).	
bg(I,J):- bg(I,J,1).					
				
pl(0,NChars):- pinta_n_chars(2,NChars).					
pl(1,NChars):- pinta_n_chars(3,NChars).	
pl(X):- pl(X,1).					
				

write_sub(Lang,SubId):- 		
		msg(Lang,SubId,Sub),
		write(Sub),nl.


read_op(Lang,SubId,Value):- 
		write_sub(Lang,SubId),
		write('>'), 
		read(Value).

choose_language(Lang):-
		repeat,
			read_op(_,choose_language,Lang),
			lang(Lang),
		!.

choose_mode(Lang,Mode):-
		repeat,
			read_op(Lang,mode,Mode),
			between(0,3, Mode),
		!.












/******************************************************************************
*******************************************************************************
******************                                           ******************
******************               DISPLAYING GAME             ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/
			

print_linha_recursive(_,[],_).
print_linha_recursive(Tabuleiro,[H|T],I):- I < 6, 
		print_celula_recursive_top(Tabuleiro,H,I,0), nl, 
		print_celula_recursive_middle(Tabuleiro,H,I,0), nl, 
		print_celula_recursive_bottom(Tabuleiro,H,I,0), nl, 
		I1 is I+1,
		print_linha_recursive(Tabuleiro,T,I1).
					
					
print_celula_recursive_top(_,[],_,_).			
print_celula_recursive_top(Tabuleiro,[H|T],I,J) :- 
		print_celula_top(Tabuleiro,H,I,J),!,
		J1 is J+1,
		print_celula_recursive_top(Tabuleiro,T,I,J1).

print_celula_recursive_middle(_,[],_,_).			
print_celula_recursive_middle(Tabuleiro,[H|T],I,J) :- 
		print_celula_middle(Tabuleiro,H,I,J),!,
		J1 is J+1,
		print_celula_recursive_middle(Tabuleiro,T,I,J1).
									
print_celula_recursive_bottom(_,[],_,_).			
print_celula_recursive_bottom(Tabuleiro,[H|T],I,J) :- 
		print_celula_bottom(Tabuleiro,H,I,J),!,
		J1 is J+1,
		print_celula_recursive_bottom(Tabuleiro,T,I,J1).

/** imprime a linha de cima de uma celula **/
print_celula_top(_,[],0,J):- bg(0,J,7),!.
print_celula_top(_,[H,T],0,_):- 0 is T mod 2, T =\= 0, pl(H,7),!.
print_celula_top(_,[H,0],0,J):- pl(H), bg(0,J,5),pl(H),!.
print_celula_top(_,[H,1],0,J):- bg(0,J),pl(H,3), bg(0,J,3),!.
print_celula_top(_,[H,3],0,J):- bg(0,J), pl(H,5),bg(0,J),!.
print_celula_top(_,[H,5],0,J):- bg(0,J), pl(H,5),bg(0,J),!.
print_celula_top(_,[H,7],0,J):- bg(0,J,3), pl(H,3), bg(0,J),!.

print_celula_top(Tabuleiro,[],I,J):- I =\= 0, I1 is I-1, 
		gameboard_select(Tabuleiro,I1,J,[RetH,RetT]),
		1 is RetT mod 2,
		bg(I,J,3),pl(RetH),bg(I,J,3).

print_celula_top(Tabuleiro,[Pl,0],I,J):- I =\= 0, I1 is I-1, 
		gameboard_select(Tabuleiro,I1,J,[RetH,RetT]),
		1 is RetT mod 2,
		pl(Pl),bg(I,J,2),pl(RetH),bg(I,J,2),pl(Pl),!.
									
print_celula_top(Tabuleiro,H,I,J):- I =\= 0, I1 is I-1, 
		gameboard_select(Tabuleiro,I1,J,[_,RetT]),
		0 is RetT mod 2,
		Imod is I mod 2,
		J1 is J + Imod,
		print_celula_top(Tabuleiro,H,0,J1).							
							
print_celula_top(Tabuleiro,H,I,J):- I =\= 0, I1 is I-1, 
		gameboard_select(Tabuleiro,I1,J,[]),
		Imod is I mod 2,
		J1 is J + Imod,
		print_celula_top(Tabuleiro,H,0,J1).	
														
							
/* imprime a linha de baixo de uma celula */
print_celula_bottom(_,[],5,J):- bg(5,J,7),!.
print_celula_bottom(_,[H,T],5,_):- 0 is T mod 2, T =\= 4, pl(H,7),!.
print_celula_bottom(_,[H,4],5,J):- pl(H), bg(5,J,5),pl(H),!.
print_celula_bottom(_,[H,3],5,J):- bg(5,J),pl(H,3), bg(5,J,3),!.
print_celula_bottom(_,[H,1],5,J):- bg(5,J), pl(H,5),bg(5,J),!. 
print_celula_bottom(_,[H,7],5,J):- bg(5,J), pl(H,5),bg(5,J),!.
print_celula_bottom(_,[H,5],5,J):- bg(5,J,3), pl(H,3), bg(5,J),!. 

print_celula_bottom(Tabuleiro,[],I,J):- I =\= 5, I1 is I+1, 
		gameboard_select(Tabuleiro,I1,J,[RetH,RetT]),
		1 is RetT mod 2,
		bg(I,J,3),pl(RetH),bg(I,J,3).

print_celula_bottom(Tabuleiro,[Pl,4],I,J):- I =\= 5, I1 is I+1, 
		gameboard_select(Tabuleiro,I1,J,[RetH,RetT]),
		1 is RetT mod 2,
		pl(Pl),bg(I,J,2),pl(RetH),bg(I,J,2),pl(Pl),!.									

print_celula_bottom(Tabuleiro,H,I,J):- I =\= 5, I1 is I+1, 
		gameboard_select(Tabuleiro,I1,J,[_,RetT]),
		0 is RetT mod 2,
		Imod is I mod 2,
		RImod is 1 - Imod,
		J1 is J + RImod,
		print_celula_bottom(Tabuleiro,H,5,J1).							
							
print_celula_bottom(Tabuleiro,H,I,J):- I =\= 5, I1 is I+1, 
		gameboard_select(Tabuleiro,I1,J,[]),
		Imod is I mod 2,
		RImod is 1 - Imod,
		J1 is J + RImod,
		print_celula_bottom(Tabuleiro,H,5,J1).	


/* imprime a linha do centro de uma celula */
print_celula_middle(Tabuleiro,H,I,J):- 
		print_celula_middle_left(Tabuleiro,H,I,J), 
		print_celula_middle_center(Tabuleiro,H,I,J), 
		print_celula_middle_right(Tabuleiro,H,I,J).


print_celula_middle_left(_,[],I,0):- bg(I,0),!.
print_celula_middle_left(_,[_,6],I,0):- bg(I,0),!.
print_celula_middle_left(_,[H,T],_,0):- T =\= 6, pl(H),!.

print_celula_middle_left(Tabuleiro,_,I,J):- J =\= 0, J1 is J-1, 
		gameboard_select(Tabuleiro,I,J1,[RetH,RetT]),
		1 is RetT mod 2,
		pl(RetH).
									
print_celula_middle_left(Tabuleiro,H,I,J):- J =\= 0, J1 is J-1, 
		gameboard_select(Tabuleiro,I,J1,[_,RetT]),
		0 is RetT mod 2,
		Jmod is J mod 2,
		I1 is I + Jmod,
		print_celula_middle_left(Tabuleiro,H,I1,0).							
	
print_celula_middle_left(Tabuleiro,H,I,J):- J =\= 0, J1 is J-1, 
		gameboard_select(Tabuleiro,I,J1,[]),
		Jmod is J mod 2,
		I1 is I + Jmod,
		print_celula_middle_left(Tabuleiro,H,I1,0).	
									
									
print_celula_middle_center(_,[],I,J):- bg(I,J,5),!.
print_celula_middle_center(_,[H,T],_,_):- 1 is T mod 2, pl(H,5),!.
print_celula_middle_center(_,[H,6],I,J):- bg(I,J,2),pl(H,3),!.
print_celula_middle_center(_,[H,2],I,J):- pl(H,3), bg(I,J,2),!.
print_celula_middle_center(_,[H,0],I,J):- pl(H,2),bg(I,J),pl(H,2),!.	
print_celula_middle_center(_,[H,4],I,J):- pl(H,2),bg(I,J),pl(H,2),!.	


print_celula_middle_right(_,[],I,5):- bg(I,5),!.
print_celula_middle_right(_,[_,2],I,5):- bg(I,5),!.
print_celula_middle_right(_,[H,T],_,5):- T =\= 2, pl(H),!.

print_celula_middle_right(Tabuleiro,_,I,J):- J =\= 5, J1 is J+1, 
		gameboard_select(Tabuleiro,I,J1,[RetH,RetT]),
		1 is RetT mod 2,
		pl(RetH).
									
print_celula_middle_right(Tabuleiro,H,I,J):- J =\= 5, J1 is J+1, 
		gameboard_select(Tabuleiro,I,J1,[_,RetT]),
		0 is RetT mod 2,
		Jmod is J mod 2,
		RJmod is 1 - Jmod,
		I1 is I + RJmod,
		print_celula_middle_right(Tabuleiro,H,I1,5).							
	
print_celula_middle_right(Tabuleiro,H,I,J):- J =\= 5, J1 is J+1, 
		gameboard_select(Tabuleiro,I,J1,[]),
		Jmod is J mod 2,
		RJmod is 1 - Jmod,
		I1 is I + RJmod,
		print_celula_middle_right(Tabuleiro,H,I1,5).	

print_outpieces_tops(_,_,_,0):- nl.
print_outpieces_tops(GSBoard,Color,Position,I):- 
		I1 is I-1,
		character(4), /** full with space **/
		print_celula_top(GSBoard,[Color,Position],0,-1),
		print_outpieces_tops(GSBoard,Color,Position,I1).								


print_outpieces_middles(_,_,_,0):- nl.
print_outpieces_middles(GSBoard,Color,Position,I):-  
		I1 is I-1,
		character(4),
		print_celula_middle_left(GSBoard,[Color,Position],-1,0),
		print_celula_middle_center(GSBoard,[Color,Position],-1,-1),
		print_celula_middle_right(GSBoard,[Color,Position],-1,5),
		print_outpieces_middles(GSBoard,Color,Position,I1).								
print_outpieces_bottoms(_,_,_,0):- nl.
print_outpieces_bottoms(GSBoard,Color,Position,I):- 
		I1 is I-1,
		character(4),
		print_celula_bottom(GSBoard,[Color,Position],5,-1),
		!, print_outpieces_bottoms(GSBoard,Color,Position,I1).								


print_outpieces_bottom([GSBoard,CurrentPlayer,PiecesLeft,PlayingColor|_]):-
		player_color(CurrentPlayer,PlayingColor,Color),
		player_pieces_left(CurrentPlayer,PiecesLeft,NPieces),
		nl,
		minor(NPieces,5, NLine0),
		print_outpieces_tops(GSBoard,Color,0,NLine0),
		print_outpieces_middles(GSBoard,Color,0,NLine0),
		print_outpieces_bottoms(GSBoard,Color,0,NLine0),
		nl,
		NLine1 is NPieces - NLine0,
		print_outpieces_tops(GSBoard,Color,0,NLine1),
		print_outpieces_middles(GSBoard,Color,0,NLine1),
		print_outpieces_bottoms(GSBoard,Color,0,NLine1).

display_game([GSBoard|GSExtraData]) :- clean_page,
		print_linha_recursive(GSBoard,GSBoard,0),
		print_outpieces_bottom([GSBoard|GSExtraData]).	














/******************************************************************************
*******************************************************************************
******************                                           ******************
******************          AUXILIAR FUNCTIONAL RULES        ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

coords_angle(1,0,0).
coords_angle(0,1,2).
coords_angle(-1,0,4).
coords_angle(0,-1,6).

possible_move_type(slide).
possible_move_type(place).
possible_extra_move_type(slide).
possible_extra_move_type(place).
possible_extra_move_type(pivot).
possible_extra_move_type(pick).
possible_extra_move_type(activate).

switch_player([GSh,1|GSt],[GSh,0|GSt]).
switch_player([GSh,0|GSt],[GSh,1|GSt]).

minusone_or_zero_or_one(-1).
minusone_or_zero_or_one(1).
minusone_or_zero_or_one(0).

adjacently_free(GSBoard,I,J,I1,J1):- 
		coords_angle(I1,J1,Angle),
		If is I-I1, Jf is J+J1,
		If >= 0, If =< 5, Jf >= 0, Jf =< 5,
		gameboard_select(GSBoard,If,Jf,Cell),
		SimetricAngle is ((Angle+4) mod 8),
		empty_or_position(Cell,SimetricAngle).
adjacently_free(_,I,_,1,0):-I+1 > 5.
adjacently_free(_,_,J,0,1):-J+1 > 5.
adjacently_free(_,I,_,-1,0):-(I-1) < 0.
adjacently_free(_,_,J,0,-1):-(J-1) < 0.

coord(C):- between(0,5,C).
angle(A):- between(0,7,A), 1 is A mod 2.
angle(A):- between(0,7,A), 0 is A mod 2.

rotateaquarterP(AngPos,NewAngPos) :-
		NewAngPos is ((AngPos+2) mod 8). 
rotateaquarterN(AngPos,NewAngPos) :- 
		NewAngPos is ((AngPos-2) mod 8). 

player_color(Player,PlayingColor,Color):- 
		list_select(PlayingColor,Player,Color).

player_pieces_left(Player,PiecesLeft,NPieces):- 
		list_select(PiecesLeft,Player,NPieces).
player_rmv_pieces_left(Player,PiecesLeft,NewPiecesLeft):-
		OtherPlayer is (Player+1) mod 2,
		list_select(PiecesLeft,Player,N),
		N1 is N-1,
		list_select(PiecesLeft,OtherPlayer,N2),
		list_update([0,0],Player,N1,Ret),
		list_update(Ret,OtherPlayer,N2,NewPiecesLeft).

player_add_pieces_left(Player,PiecesLeft,NewPiecesLeft):-
		OtherPlayer is (Player+1) mod 2,
		list_select(PiecesLeft,Player,N),
		N1 is N+1,
		list_select(PiecesLeft,OtherPlayer,N2),
		list_update([0,0],Player,N1,Ret),
		list_update(Ret,OtherPlayer,N2,NewPiecesLeft).

empty_or_position([],_):-!.
empty_or_position([_,Position],Position).


adjacently_occupying(GSBoard,I,J,I1,J1):- 
		coords_angle(I1,J1,_),
		If is I-I1, Jf is J+J1,
		gameboard_select(GSBoard,If,Jf,[_,Pos]),
		1 is Pos mod 2.

count_adjacently_free(GSBoard,I,J,Nr):-
		findall(I1-J1,adjacently_free(GSBoard,I,J,I1,J1),Solutions),
		length(Solutions,Nr).


count_adjacently_occupying(GSBoard,I,J,Nr):-
		findall(I1-J1,adjacently_occupying(GSBoard,I,J,I1,J1),Solutions),
		length(Solutions,Nr).

possible_to_insert(GSBoard,I,J,_):- 
		gameboard_select(GSBoard,I,J,[_,_]),!,fail. /* that house is not empty*/

possible_to_insert(GSBoard,I,J,AngPos):-  
		possible_anglenposition(I,J,AngPos),
		1 is AngPos mod 2, 
		count_adjacently_free(GSBoard,I,J,4).

possible_to_insert(GSBoard,I,J,AngPos):-  
		possible_anglenposition(I,J,AngPos),
		0 is AngPos mod 2, 
		count_adjacently_free(GSBoard,I,J,N), /** garants that it cant be active*/
		N < 4,
		count_adjacently_occupying(GSBoard,I,J,0).

possible_to_insert(GSBoard,I,J,AngPos):- 
		possible_anglenposition(I,J,AngPos),
		0 is AngPos mod 2, 
		count_adjacently_free(GSBoard,I,J,N),  /** garants that it cant be active*/
		N < 4,
		count_adjacently_occupying(GSBoard,I,J,1),
		coords_angle(I1,J1,AngPos),
		adjacently_occupying(GSBoard,I,J,I1,J1).

possible_anglenposition(I,J,AngPos):- 
		coord(I), 
		coord(J), 
		angle(AngPos).

/** is_computer_turn ... (CurrentPlayer, Mode) **/
is_computer_turn_easy(1,1).
is_computer_turn_easy(0,3).

is_computer_turn_normal(1,2).
is_computer_turn_normal(1,3).

is_computer_turn(X,Y):- is_computer_turn_easy(X,Y).
is_computer_turn(X,Y):- is_computer_turn_normal(X,Y).








/******************************************************************************
*******************************************************************************
******************                                           ******************
******************    GAMEBOARD GENERATION / MAINTENANCE     ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

gameboard_new(Gameboard):- gameboard_new(6,Gameboard),!.

gameboard_new(0,[]).
gameboard_new(I,[GameboardH|GameboardT]):- I1 is I-1,
		gameboard_new_line(6,GameboardH),
		!, gameboard_new(I1,GameboardT).										

gameboard_new_line(0,[]).
gameboard_new_line(J,[[]|T]):- J1 is J-1,
		!, gameboard_new_line(J1,T).



gameboard_line_update([Gh|Gt],I,J,C,I1,[Gh|GNt]):- I1 < I,
		I2 is I1+1,
		gameboard_line_update(Gt,I,J,C,I2,GNt).
gameboard_line_update([Gh|Gt],I,J,C,I,[GNh|Gt]):- 
		gameboard_linecell_update(Gh,J,C,0,GNh).

gameboard_linecell_update([_|Lt],J,C,J,[C|Lt]).
gameboard_linecell_update([Lh|Lt],J,C,J1,[Lh|NLt]):- J1 < J,
		J2 is J1+1,
		gameboard_linecell_update(Lt,J,C,J2,NLt).


gameboard_update(Gameboard,I,J,C,NewGameboard):- 
		gameboard_line_update(Gameboard,I,J,C,0,NewGameboard).


gameboard_select(X,I,J,Ret2) :- I >= 0, J >= 0, I =< 5, J =< 5,
		list_select(X,I,Ret),
		list_select(Ret,J,Ret2).

gameboard_clear_path_rest(_,I,J,I,J,_,_):- !.
gameboard_clear_path_rest(Gameboard,Is,Js,Ie,Je,UniDi,UniDj):-
		gameboard_select(Gameboard,Is,Js,[]),
		NextI is Is + UniDi,
		NextJ is Js + UniDj,
		gameboard_clear_path_rest(Gameboard,NextI,NextJ,Ie,Je,UniDi,UniDj).

gameboard_clear_path(Gameboard,Is,Js,Ie,Je):- 
		between(0,5,Is),between(0,5,Js),between(0,5,Ie),between(0,5,Je),
		Di is (Ie-Is),
		Dj is (Je-Js),
		oneof2iszero(Di,Dj), 
		unidelta(Di,UniDi),unidelta(Dj,UniDj),
		NextI is Is + UniDi,
		NextJ is Js + UniDj,
		gameboard_clear_path_rest(Gameboard,NextI,NextJ,Ie,Je,UniDi,UniDj).




















/******************************************************************************
*******************************************************************************
******************                                           ******************
******************       EXECUTING MOVES - PC/PLAYERS        ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/


rotate_adjpieceslidin(GameBoard,I,J,K,NewGameboard):-
		gameboard_select(GameBoard,I,J,[Player,AngPos]),
		1 is AngPos mod 2,
		NewAngPos is (K+AngPos) mod 8,
		gameboard_update(GameBoard,I,J,[Player,NewAngPos],NewGameboard).
rotate_adjpieceslidin(GameBoard,_,_,_,GameBoard). 

rotate_adj(Gameboard,I,J,DirI,DirJ,NewGameboard):-
		coords_angle(DirI,DirJ,Angl),
		rotateaquarterP(Angl,Pang),
		rotateaquarterN(Angl,Nang),
		coords_angle(Pi,Pj,Pang),
		coords_angle(Ni,Nj,Nang),
		kversor(DirI,DirJ,Pi,Pj,Pk),
		kversor(DirI,DirJ,Ni,Nj,Nk),
		RPi is I+(-1*Pi), RPj is J+Pj, RNi is I+(-1*Ni), RNj is J+Nj,
		rotate_adjpieceslidin(Gameboard,RPi,RPj,Pk,TmpGameboard),
		rotate_adjpieceslidin(TmpGameboard,RNi,RNj,Nk,NewGameboard).


animate_slide([Gameboard|ExtData],I,J,I,J,UniDi,UniDj,Color,AngPos,ResBoard):-
		FlipI is -1*UniDi,	
		rotate_adj(Gameboard,I,J,FlipI,UniDj,TmpBoard0),
		coords_angle(FlipI,UniDj,TmpAng),
		gameboard_update(TmpBoard0,I,J,[Color,TmpAng],TmpBoard1),
		display_game([TmpBoard1|ExtData]),
		sleep(1),
		gameboard_update(TmpBoard1,I,J,[Color,AngPos],ResBoard),!.

animate_slide([Gameboard|ExtData],Is,Js,Ie,Je,UniDi,UniDj,Color,AngPos,ResBoard):-
		NextI is Is + UniDi,
		NextJ is Js + UniDj,
		FlipI is -1*UniDi,	
		rotate_adj(Gameboard,Is,Js,FlipI,UniDj,TmpBoard0),
		coords_angle(FlipI,UniDj,TmpAng),
		gameboard_update(TmpBoard0,Is,Js,[Color,TmpAng],TmpBoard1),
		display_game([TmpBoard1|ExtData]),
		sleep(1),
		gameboard_update(TmpBoard1,Is,Js,[],TmpBoard2),
		animate_slide([TmpBoard2|ExtData],NextI,NextJ,Ie,Je,UniDi,UniDj,Color,AngPos,ResBoard).

animate_slide([Gameboard|ExtData],Is,Js,Ie,Je,Color,AngPos,ResBoard):-
		Di is (Ie-Is),
		Dj is (Je-Js),
		unidelta(Di,UniDi),unidelta(Dj,UniDj),
		animate_slide([Gameboard|ExtData],Is,Js,Ie,Je,UniDi,UniDj,Color,AngPos,ResBoard).

make_move(GSBoard,[pass],GSBoard).
make_move(GSBoard,[exit],GSBoard).
make_move(GSBoard,[no],GSBoard).

make_move([GSBoard,CurPl,PcsLft,PlClr|T],[slide,[Is,Js],[Ie,Je],AngPos],[NGSBoard,CurPl,PcsLft,PlClr|T]):-
		player_color(CurPl,PlClr,Color),
		animate_slide([GSBoard,CurPl,PcsLft,PlClr|T],Is,Js,Ie,Je,Color,AngPos,NGSBoard).


make_move([GSBoard,CurPl,PcsLft,PlClr|T],[place,[I,J],AngPos],[NGSBoard,CurPl,NewPcsLft,PlClr|T]):-
		player_rmv_pieces_left(CurPl,PcsLft,NewPcsLft),	
		player_color(CurPl,PlClr,Color),
		gameboard_update(GSBoard,I,J,[Color,AngPos],NGSBoard).  

make_move([GSBoard,CurPl,PcsLft,PlClr|T],[pivot,[I,J],AngPos],[NGSBoard,CurPl,PcsLft,PlClr|T]):-
		player_color(CurPl,PlClr,Color),
		gameboard_update(GSBoard,I,J,[Color,AngPos],NGSBoard).  

make_move([GSBoard,CurPl,PcsLft,PlClr|T],[activate,[I,J],AngPos],[NGSBoard,CurPl,PcsLft,PlClr|T]):-
		player_color(CurPl,PlClr,Color),
		gameboard_update(GSBoard,I,J,[Color,AngPos],NGSBoard).  

make_move([GSBoard,CurPl,PcsLft,PlClr|T],[pick,[I,J]],[NGSBoard,CurPl,NewPcsLft,PlClr|T]):-
		player_add_pieces_left(CurPl,PcsLft,NewPcsLft),	
		gameboard_update(GSBoard,I,J,[],NGSBoard).  



make_move([GSBoard,CurPl,PcsLft,PlClr,0|T],[draw],[GSBoard,CurPl,PcsLft,PlClr,1|T]):-!.
make_move([_,_,_,PlClr,1,Md,Rs,FrstPl],[draw],[NGSBoard,FrstPl,[10,10],NPlCrl,0,Md,Rs,OtherFrstPl]):-
		OtherFrstPl is (FrstPl+1) mod 2,
		gameboard_new(NGSBoard),
		list2_swap(PlClr,NPlCrl).















/******************************************************************************
*******************************************************************************
******************                                           ******************
******************        CALCULATING AVAILABLE MOVES        ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

valid_move(slide,[GSBoard,CurPl|_],Move):-
		coord(Is),coord(Js), /** choose start position **/
		gameboard_select(GSBoard,Is,Js,[CurPl|Ang]),
		1 is Ang mod 2,
		coord(Ie),coord(Je),  /** choose end position **/
		different_cells([Is,Js],[Ie,Je]),
		gameboard_clear_path(GSBoard,Is,Js,Ie,Je),
		angle(AngPos),  /** choose final angle **/
		Di is -1*(Ie-Is),
		Dj is (Je-Js),
		unidelta(Di,UniDi),unidelta(Dj,UniDj),
		rotate_adj(GSBoard,Ie,Je,UniDi,UniDj,TmpGSBoard0),
		gameboard_update(TmpGSBoard0,Is,Js,[],TempGSBoard),
		possible_to_insert(TempGSBoard,Ie,Je,AngPos),
		Move = [slide,[Is,Js],[Ie,Je],AngPos].
valid_move(place,[GSBoard,CurPl,PcsLft|_],Move):- 
		player_pieces_left(CurPl,PcsLft,Pices), 
		Pices > 0,
		coord(I),coord(J), /** choose place position */
		angle(AngPos),  /** choose place angle **/
		possible_to_insert(GSBoard,I,J,AngPos),
		Move = [place,[I,J],AngPos].

valid_extra_move(slide,GameState,_,Move):- 
		valid_move(slide,GameState,Move).
valid_extra_move(place,GameState,_,Move):- 
		valid_move(place,GameState,Move).	
valid_extra_move(pick,[Gameboard,CurPl|_],LastPlaydPiece,Move):- 
		coord(Ip),coord(Jp), /** choose pick piece position */
		gameboard_select(Gameboard,Ip,Jp,[CurPl|_]),
		different_cells([Ip,Jp],LastPlaydPiece),
		Move = [pick,[Ip,Jp]].
valid_extra_move(activate,[Gameboard,CurPl|_],Move,_):- 
		coord(Ia),coord(Ja), /** choose piece to activate  */
		angle(ActiveAngle),  /** choose angle to leave it **/
		1 is ActiveAngle mod 2,
		gameboard_select(Gameboard,Ia,Ja,[CurPl|Ang]),
		0 is Ang mod 2,
		count_adjacently_free(Gameboard,Ia,Ja,N),
		4 is N,
		Move = [activate,[Ia,Ja],ActiveAngle].
valid_extra_move(pivot,[Gameboard,CurPl|_],Move,_):-
		coord(Ipv),coord(Jpv), /** choose piece position to pivot **/
		angle(PivAngle), /** choose angle to piv */
		1 is PivAngle mod 2,
		gameboard_select(Gameboard,Ipv,Jpv,[CurPl|Ang]),
		1 is Ang mod 2,
		count_adjacently_free(Gameboard,Ipv,Jpv,N),
		4 is N,
		Move = [pivot,[Ipv,Jpv],PivAngle].


valid_move(Gamestate,Move):- 
	possible_move_type(MoveType),
	valid_move(MoveType,Gamestate,Move).

valid_extra_move(Gamestate,LastPlayedPiece,Move):- 
	possible_extra_move_type(MoveType),
	valid_extra_move(MoveType,Gamestate,LastPlayedPiece,Move).
	











/******************************************************************************
*******************************************************************************
******************                                           ******************
******************            LANGUAGE PREDICATES            ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

lang(en).
lang(pt).

/*International*/
msg(_,confirmation,'Ok.').
msg(_,choose_language,'Choose the language:\nEscolhe a Linguagem:\n\n\n\nEnglish. (en)\nPortugues. (pt)\n').


/*English*/
msg(en,mode,'Player vs Player. (0)\nPlayer vs Computer-Easy (1)\nPlayer vs Computer-Normal (2)\nComputer-Easy vs Computer-Normal (3)').
msg(en,move,'What you wanna do?    (place,slide,draw,exit)' ).
msg(en,slide,'What piece do you want to slide?    (I-J)').
msg(en,draw,'Your opponent asked for draw. Do you accept?    (draw,no,exit)').
msg(en,position,'Slide it to where?    (I-J)').
msg(en,slide_position,'Where it will be played?    (I-J)').
msg(en,angle,'And in what angle you want to leave it?    (1,3,5,7)').
msg(en,extra_move,'You have got an extra move. What you wanna do?    (place,slide,activate,pivot,pick,pass)').
msg(en,pick,'What piece do you want to pick?    (I-J)' ).
msg(en,activate,'What piece do you want to activate?    (I-J)').
msg(en,pivot,'What piece do you want to pivot?    (I-J)').
msg(en,error,'Oops, bad option move/value/angle/value.').
msg(en,end_turn,'End of turn. \n\n\n Next player turn.').


/*Portuguese*/
msg(pt,mode,'Jogador vs Jogador. (0)\nJogador vs Computador-Facil (1)\nJogador vs Computador-Normal (2)\nComputador-Facil vs Computador-Normal (3)').
msg(pt,move,'O que vais fazer?    (place,slide,draw,exit)' ).
msg(pt,slide,'Que peca queres mover?    (I-J)').
msg(pt,draw,'O teu adversario esta a pedir-te um empate. Aceitas?    (draw,no,exit)').
msg(pt,position,'Onde vai ser jogada a peca?    (I-J)').
msg(pt,slide_position,'Para onde queres deslizar a peça?    (I-J)').
msg(pt,angle,'Em que angulo fica?    (1,3,5,7)').
msg(pt,extra_move,'Tens direito a um movimento extra. O que queres fazer?    (place,slide,activate,pivot,pick,pass)').
msg(pt,pick,'Que peca desejas tirar?    (I-J)' ).
msg(pt,activate,'Que peca desejas ativar?    (I-J)').
msg(pt,pivot,'Que peca desejas pivotar?    (I-J)').
msg(pt,error,'Oops, a opcao escolhida nao e valida (movimento/posicao/angulo/valor).').
msg(pt,end_turn,'Terminou o turno. \n\n\n E a vez do proximo jogador.').





/*
/******************************************************************************
*******************************************************************************
******************                                           ******************
******************         CHOOSING MOVES - PLAYERS/PC       ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/

evaluate_move([activate,[_,_],_], _,250).
evaluate_move([place,[_,_],AngPos],_, 200):- 1 is AngPos mod 2,!.
evaluate_move([place,[_,_],AngPos],_, 150):- 0 is AngPos mod 2,!.
evaluate_move([slide,[_,_],[_,_],AngPos],_, 110):- 1 is AngPos mod 2 ,!.
evaluate_move([slide,[_,_],[_,_],AngPos],_, 90):- 0 is AngPos mod 2 ,!.

evaluate_move([pick,[_,_]],[_,CurPl,PiecesLeft|_],250):-
		player_pieces_left(CurPl,PiecesLeft,Pieces), 
		0 =< Pieces.

evaluate_move(_, _, 50):-!.

make_evaluators_keylist([], []).
make_evaluators_keylist([evaluate_move(X,Y,_)|T], [Key-evaluate_move(X,Y,Z)|T1]):-
		evaluate_move(X, Y, Z),
		Key is 1000 - Z, /** cheat to invert sorted order **/
		make_evaluators_keylist(T, T1).


/** PC - easy **/
choose_extra_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],LastPlaydPiece,Move,_):-
		is_computer_turn_easy(CurPl,Md),
		write('Hmm,let me think ...'),
		sleep(2),
		valid_extra_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],LastPlaydPiece,Move),!.

/**PC - normal **/
choose_extra_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],LastPlaydPiece,Move,_):-
		is_computer_turn_normal(CurPl,Md),
		write('Hmm,let me think ...'),
		sleep(2),
		valid_extra_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],LastPlaydPiece,Move),!.



choose_extra_move(GameState, LastPlaydPiece, Move,Lang):-
		repeat,
			read_op(Lang,extra_move,Cmd),
	 		choose_extra_move_details(Cmd,GameState,LastPlaydPiece,Move,Lang),
		!.
choose_extra_move_details(pass,_,_,[pass],_).
choose_extra_move_details(slide,GameState,_,Move,_):- 
		choose_move_details(slide,GameState,Move,_).
choose_extra_move_details(place,GameState,_,Move,_):- 
		choose_move_details(place,GameState,Move,_).
choose_extra_move_details(pick,[Gameboard,CurPl|_],LastPlaydPiece,Move,Lang):- 
		read_op(Lang,pick,Ip-Jp),
		gameboard_select(Gameboard,Ip,Jp,[CurPl|_]),
		different_cells([Ip,Jp],LastPlaydPiece),
		Move = [pick,[Ip,Jp]].
choose_extra_move_details(activate,[Gameboard,CurPl|_],Move,_,Lang):- 
		read_op(Lang,activate,Ia-Ja),
		read_op(Lang,angle,ActiveAngle),
		1 is ActiveAngle mod 2,
		gameboard_select(Gameboard,Ia,Ja,[CurPl|Ang]),
		0 is Ang mod 2,
		count_adjacently_free(Gameboard,Ia,Ja,N),
		4 is N,
		Move = [activate,[Ia,Ja],ActiveAngle].
choose_extra_move_details(pivot,[Gameboard,CurPl|_],Move,_,Lang):-
		read_op(Lang,pivot,Ipv-Jpv),
		read_op(Lang,angle,PivAngle),
			1 is PivAngle mod 2,
		gameboard_select(Gameboard,Ipv,Jpv,[CurPl|Ang]),
		1 is Ang mod 2,
		count_adjacently_free(Gameboard,Ipv,Jpv,N),
		4 is N,
		Move = [pivot,[Ipv,Jpv],PivAngle].
choose_extra_move_details(_,_,_,_,Lang):-
		write_sub(Lang,error),nl,
		fail.




/** PC rejects all draws **/
choose_move([_,CurPl,_,_,1,Md,_,_],[no],_):- 
		is_computer_turn(CurPl,Md).


/** PC - easy **/
choose_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],Move,_):-
		is_computer_turn_easy(CurPl,Md),
		write('Hmm,let me think ...'),
		sleep(2),
		valid_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],Move),!.

/** PC - normal **/
choose_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],Move,_):-
		is_computer_turn_normal(CurPl,Md),
		write('Hmm,let me think      ...'),
		sleep(2),
		findall(evaluate_move(Move,[GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],_),valid_move([GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl],Move),Solutions),
		make_evaluators_keylist(Solutions,KeySolutions),
		keysort(KeySolutions,[_-evaluate_move(Move,_,_)|_]),
		!.
choose_move([_,_,_,_,1|_],Move,Lang):-
		repeat,
			read_op(Lang,draw,Cmd),
	 		choose_move_details(Cmd,_,Move,Lang),
		!.
choose_move(GameState,Move,Lang):-
		repeat,
			read_op(Lang,move,Cmd),
	 		choose_move_details(Cmd,GameState,Move,Lang),
 		!.
					

choose_move_details(no,_,[no],_).
choose_move_details(draw,_,[draw],_).
choose_move_details(exit,_,[exit],_).
choose_move_details(draw,_,_,_).
choose_move_details(slide,[GSBoard,CurPl|_],Move,Lang):- 
		read_op(Lang,slide,Is-Js),
		gameboard_select(GSBoard,Is,Js,[CurPl|Ang]),
		1 is Ang mod 2,
		read_op(Lang,position,Ie-Je),
		different_cells([Is,Js],[Ie,Je]),
		gameboard_clear_path(GSBoard,Is,Js,Ie,Je),
		read_op(Lang,angle, AngPos),
		Di is -1*(Ie-Is),
		Dj is (Je-Js),
		unidelta(Di,UniDi),unidelta(Dj,UniDj),
		rotate_adj(GSBoard,Ie,Je,UniDi,UniDj,TmpGSBoard0),
		gameboard_update(TmpGSBoard0,Is,Js,[],TempGSBoard),
		possible_to_insert(TempGSBoard,Ie,Je,AngPos),
		Move = [slide,[Is,Js],[Ie,Je],AngPos], !.
choose_move_details(place,[GSBoard,CurPl,PcsLft|_],Move,Lang):- 
		player_pieces_left(CurPl,PcsLft,Pices),
		Pices > 0,
		read_op(Lang,position,I-J),
		read_op(Lang,angle,AngPos),
		possible_to_insert(GSBoard,I,J,AngPos),
		Move = [place,[I,J],AngPos].
choose_move_details(_,_,_,Lang):-
		write_sub(Lang,error),nl, fail.






/******************************************************************************
*******************************************************************************
******************                                           ******************
******************           GAME STATE / MAIN LOOP          ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/ 







game_over([GSBoard,_,PcsLft,[C1,C2],PndDrw,Md,[Rs0,Rs1],FrstPl],Lang):-
		player_pieces_left(0,PcsLft,N),
		N =\= 10,
		not(valid_move([GSBoard,0,PcsLft,[C1,C2],PndDrw,Md,[Rs0,Rs1],FrstPl], [slide|_])),
		RsN is Rs1+1,
		toggle(FrstPl,NFrstPl),
		gameboard_new(NGSBoard),

		clean_page,
		write('Game is over.\n The winner is Player 1'), nl,
		write(RsN), write(' Player 1'), nl,
		write(Rs1), write(' Player 2'),nl,
		read(_),

		!, play_turn([NGSBoard,NFrstPl,[10-10],[C2,C1],0,Md,[Rs0,RsN],NFrstPl],Lang).

game_over([GSBoard,_,PcsLft,[C1,C2],PndDrw,Md,[Rs0,Rs1],FrstPl],Lang):-
		player_pieces_left(1,PcsLft,N),
		N =\= 10,
		not(valid_move([GSBoard,1,PcsLft,[C1,C2],PndDrw,Md,[Rs0,Rs1],FrstPl], [slide|_])),
		RsN is Rs0+1,
		toggle(FrstPl,NFrstPl),
		gameboard_new(NGSBoard),		
		
		clean_page,
		write('Game is over.\n The winner is Player 2'), nl,
		write(RsN), write(' Player 2'), nl,
		write(Rs0), write(' Player 1'),nl,
		read(_),

		!, play_turn([NGSBoard,NFrstPl,[10-10],[C2,C1],0,Md,[RsN,Rs1],NFrstPl],Lang).


/** Gamestate is aka [GSBoard,CurPl,PcsLft,PlClr,PndDrw,Md,Rs,FrstPl] **/
initialize_game(Mode0, [GSBoard,CurrentPlayer,PiecesLeft,PlayingColor,PendingDraw,Mode,Result,FirstPlayer]):- 
		gameboard_new(GSBoard),
		PiecesLeft = [10,10],
		PlayingColor = [0,1],
		CurrentPlayer = 0,
		Mode = Mode0, /** 0 - PvsP **/
		PendingDraw = 0,
		Result = [0,0],
		FirstPlayer = 0.

play_turn(GameState,Lang):-
		display_game(GameState),!,
		choose_move(GameState,Move,Lang),
		make_move(GameState,Move,GameState1),
		prepare_next_turn(GameState1,Move,Lang).

play_extra_turn(GameState,LastPlayedPiece,Lang):-
		display_game(GameState),!,
		choose_extra_move(GameState,LastPlayedPiece,Move,Lang),
		make_move(GameState,Move,GameState1),
		!, prepare_next_turn(GameState1,Move,Lang).		


prepare_next_turn(GameState,[slide,[_,_],[If,Jf],AngPos],Lang):- 
		0 is AngPos mod 2,
		!, play_extra_turn(GameState,[If,Jf],Lang).

prepare_next_turn([Gb,CurPl|T],_,Lang):- 
		toggle(CurPl,OtherPl),
		not(game_over([Gb,OtherPl|T],Lang)),
		not(game_over([Gb,CurPl|T],Lang)),
		switch_player([Gb,CurPl|T],GameState1),
		!, play_turn(GameState1,Lang).

prepare_next_turn(_,[exit],_):- clean_page, 
		clean_page, write('Good Bye!'),!.

prepare_next_turn(_,_,_).

/**
tixel:-
		clean_page,
		choose_language(Lang),
		clean_page,	
		initialize_game(Mode,GameState),
		choose_mode(Lang,Mode),
		!,play_turn(GameState,Lang).

**/






/******************************************************************************
*******************************************************************************
******************                                           ******************
******************                 CONNECTION  	             ******************
******************                                           ******************
*******************************************************************************
*******************************************************************************/ 

port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	serverLoop(Stream),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream) :-
	repeat,
		read(Stream, ClientMsg),
		write('<-- '), write(ClientMsg), nl,
		parse_input(ClientMsg, MyReply),
		format(Stream, '~q.~n', [MyReply]),
		write('--> '), write(MyReply), nl,
		flush_output(Stream),
		(ClientMsg == quit; ClientMsg == end_of_file),
	!.

/** 
	Moves:
	[slide,[Is,Js],[Ie,Je],AngPos]. 
	[place,[I,J],AngPos].
	[pick,[Ip,Jp]].
	[activate,[Ia,Ja],ActiveAngle].
	[pivot,[Ipv,Jpv],PivAngle].
**/


complete_make_move([_,_, [Gb,CurPl|T]], [slide,[Is,Js],[If,Jf],AngPos] , [extra_move,[If,Jf],GameState1]):- 0 is AngPos mod 2,
		make_move([Gb,CurPl|T],[slide,[Is,Js],[If,Jf],AngPos],GameState1), !.

complete_make_move([_,_, GameState], [Type,[If,Jf]|T] ,[regular_move,[If,Jf],GameState2]):-
		make_move(GameState,[Type,[If,Jf]|T],GameState1),
		switch_player(GameState1,GameState2),!.


/** initialize connection **/
parse_input(initialize(Mode), [regular_move,none,GameState]) :- 
		initialize_game(Mode,GameState), !.


/** Available Pieces To Move **/
parse_input(available_pieces([regular_move,_, GameState]), AvailablePieces) :- 
		findall(Is-Js,valid_move(slide,GameState,[_,[Is,Js]|_]), AP),
		remove_dups(AP,AvailablePieces), !.

parse_input(available_pieces([extra_move,LPP, GameState]), AvailablePieces) :- 
		findall(Is-Js,valid_extra_move(slide,GameState,LPP,[_,[Is,Js],_,_]), AP1),
		findall(Is-Js,valid_extra_move(pick,GameState,LPP,[_,[Is,Js]]), AP2),
		findall(Is-Js,valid_extra_move(activate,GameState,LPP,[_,[Is,Js],_]), AP3),
		findall(Is-Js,valid_extra_move(pivot,GameState,LPP,[_,[Is,Js],_]), AP4),
		append(AP1,AP2,AP12), append(AP12,AP3,AP123), append(AP123,AP4,AP1234), 
		remove_dups(AP1234,AvailablePieces), !.



		
/** available moves for a given piece **/
parse_input(available_moves(place,[regular_move,_, GameState]), AvailablePieces) :- 
		findall(If-Jf,valid_move(place,GameState,[_,[If,Jf],_]), AP1),
		remove_dups(AP1,AvailablePieces), !.
parse_input(available_moves(Is-Js,[regular_move,_, GameState]), AvailablePieces) :- 
		findall(If-Jf,valid_move(slide,GameState,[_,[Is,Js],[If,Jf],_]), AP1),
		remove_dups(AP1,AvailablePieces), !.


parse_input(available_moves(place,[extra_move,LPP, GameState]), AvailablePieces) :- 
		findall(If-Jf,valid_extra_move(place,GameState,LPP,[_,[If,Jf],_]), AP1),
		remove_dups(AP1,AvailablePieces), !.
parse_input(available_moves(Is-Js,[extra_move,LPP, GameState]), AvailablePieces) :- 
		findall(If-Jf,valid_extra_move(slide,GameState,LPP,[_,[Is,Js],[If,Jf],_]), AP1),
		findall(If-Jf,valid_extra_move(pick,GameState,LPP,[_,[If,Jf],_]), AP2),
		findall(If-Jf,valid_extra_move(activate,GameState,LPP,[_,[If,Jf],_]), AP3),
		findall(If-Jf,valid_extra_move(pivot,GameState,LPP,[_,[If,Jf],_]), AP4),
		append(AP1,AP2,AP12), append(AP12,AP3,AP123), append(AP123,AP4,AP1234), 
		remove_dups(AP1234,AvailablePieces), !.


/** play given move **/ 
parse_input(play_move([regular_move,LPP, GameState]), [Move,GameState1]) :- 
		choose_move(GameState,Move,en),
		complete_make_move([regular_move,LPP, GameState],Move,GameState1), !.



/** choose & play a move  **/
parse_input(choose_move([MoveType,LPP, GameState]), [Move,CompleteGameState1]) :- 
		choose_move(GameState,Move,en),
		complete_make_move([MoveType,LPP, GameState],Move,CompleteGameState1), !.



/** leaving connection **/ 
parse_input(quit, good_bye) :- !.
parse_input(end_of_file, good_bye) :- !.


/** some bad command **/
parse_input(_ClientMsg, bad_request) :- !.



:-server.
