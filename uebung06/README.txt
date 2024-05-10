Übung 06

Contributors:
Rayk Kretzschmar
Bohdan Babii

Solution to Exercise 6.1 (Running time of Strassen’s algorithm)

Recurrence Relation: T(n) = 7T(n/2) + (9/2)n^2

The Master Theorem allows us to find the asymptotic behavior of recurrences of the form: T(n) = aT(n/b) + f(n)

a = 7 (number of subproblems)
b = 2 (factor by which the problem size reduces in each subproblem)
f(n) = (9/2)n^2

Calculate logb(a)
log2(7) ≈ 2.81

Since f(n) is asymptotically smaller than n^(logb(a)), the Master Theorem (case 3) applies.

Therefore, the solution to the recurrence relation is:
T(n) = Θ(n^(logb(a))) = Θ(n^log2(7))