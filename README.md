# GeneticAlgorithm

Program that allows to solve problems that don't need to have an algorithm to find an optimal solution.
As an example I use a knapsack problem, but it the core algorithm isn't problem specific and can solve any problem that can be encoded into binary representation 
(or at least find a solution very close to the optimum).

This is achieved thanks to using a simple model of evolution, derived from biological evolution. 
There are individuals that have genotypes and through applying the rule of survival of the fittest (fitment being calculated by an instance of a given problem) the least fit individuals aren't likely to pass on their genotype before being replaced by a new generation. 
Each generations fittest individual is moved into the new generation so it's genotype has a higher chance to spread.
