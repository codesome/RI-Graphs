# RI-Graphs

## Follow these steps to run the program

### Compile using C++11
```bash
$ g++ graph.cpp index.cpp -std=c++11 -o graph
```

### Execute

```bash
$ ./graph no_of_nodes probablity_for_an_edge
```

### Example

```bash
$ g++ index.cpp graph.cpp -std=c++11 -o graph
$ ./graph 10 0.3
Graph:
0->1
1->2 4 0
2->5 8 1
3->7 8 9
4->6 8 1
5->6 2
6->4 5
7->9 3
8->2 3 4
9->3 7

Shortest Paths:
0 1
0 1 2
0 1 2 8 3
0 1 4 8 3
0 1 4
0 1 2 5
0 1 4 6
0 1 2 8 3 7
0 1 4 8 3 7
0 1 2 8
0 1 4 8
0 1 2 8 3 9
0 1 4 8 3 9
1 2
1 2 8 3
1 4 8 3
1 4
1 2 5
1 4 6
1 2 8 3 7
1 4 8 3 7
1 2 8
1 4 8
1 2 8 3 9
1 4 8 3 9
2 8 3
2 8 4
2 1 4
2 5
2 5 6
2 8 3 7
2 8
2 8 3 9
3 8 4
3 8 2 5
3 8 4 6
3 7
3 8
3 9
4 6 5
4 6
4 8 3 7
4 8
4 8 3 9
5 6
5 2 8 3 7
5 2 8
5 2 8 3 9
6 4 8 3 7
6 4 8
6 4 8 3 9
7 3 8
7 9
8 3 9


Diameter
Length: 5
Path: 0---1---2---8---3---7


Radius
Length: 3
Center: 2
Path: 2---8---3---7

Betweenness Centrality:
0: 0
1: 13
2: 14
3: 18
4: 14
5: 1
6: 1
7: 0
8: 25
9: 0

```
