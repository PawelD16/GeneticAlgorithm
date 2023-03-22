# GeneticAlgorithm

Program that allows to solve problems that don't need to have an algorithm to find an optimal solution.
As an example I use a knapsack problem, but it the core algorithm isn't problem specific and can solve any problem that can be encoded into binary representation 
(or at least find a solution very close to the optimum).

I used move semantics to prevent unnecesary memory managment.
With all compilers optimization the program is even faster that way as there isn't a need to access memory from pointers.
