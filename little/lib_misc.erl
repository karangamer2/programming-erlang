-module (lib_misc).
-compile (export_all).

% Our own for control structure
for(Max, Max, F) -> [F(Max)];
for(I, Max, F) -> [F(I) | for(I+1, Max, F)].

% The world famous quicksort
quicksort([]) -> [];
quicksort([Pivot|T]) ->
  quicksort([X || X <- T, X < Pivot])
  ++ [Pivot] ++
  quicksort([X || X <- T, X > Pivot]).

% Creating pythagorean triplets
% Up to N (A^2 + B^2 = C^2)
pythagorean_triplets(N) ->
  [ {A,B,C} ||
    A <- lists:seq(1, N),
    B <- lists:seq(1, N),
    C <- lists:seq(1, N),
    A + B + C =< N,
    A * A + B * B =:= C * C
  ].

% Find all permutations of a word
permutations([]) -> [[]];
permutations(L) -> [ [H|T] || H <- L, T <- permutations(L -- [H]) ].
