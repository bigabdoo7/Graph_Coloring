# Graph_Coloring
Simulated annealing in graph coloring problem

## Results

|File    |Solution  |
|--------|----------|
|125.1   |6         |
|125.5   |22        |
|125.9   |49        |
|250.1   |11        |
|250.5   |38        |
|250.9   |89        |
|256.1   |21        |
|500.1   |18        |
|500.5   |68        |
|500.9   |168       |
|1000.1  |29        |
|1000.5  |122       |
|1000.9  |311       |

## Algritm

The greedy algoritm is a deterministic algorithm, given an order of nodes(vertices), it generates a single solution. So our simulated annealing algorithm tries to find the optimal order that produces the best solution. To find neighbours of the order, we use the 2-opt algorithm; it takes a part in the middle of a sequence, inverts it, and then reatachs it. Given that the greedy algorithm is deterministic, when computing an order's neighbour's solution, the first part is unchainged, thet's why we called our function Partial greedy, because it only calculates tha latter part.

The parameter used for simulated annealing is coolingFactor = 0.95 with an initial tempreture of 1. The temperature decreases exponentially.
For the 2-opt algorithm, we used a cut of 7 nodes.

## Compiling the code
We compiled our code using gcc version 5.4.0, in a 64bit machine.

gcc main.c misc.c 

The command above compiles the code, the option (-o name_of_output) let you choose a name for the executable. 

As requested, the executable takes a name the name of the file and adds "./pb" in the begining, and ".col" in the end. It generates a file in the same directory with the same name and extension ".sol".
