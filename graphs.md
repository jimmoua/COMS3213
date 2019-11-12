# Graphs

Let `v` and `w` be vertices of a graph. If `v` and `w` are joined by an edge
`e`, then `v` and `w` are said to be adjacent. Moreover, `v` and `w` are are
said to be incident with `e`, and `e` is said to be incident with `v` and `w`.

## Adjacency Matrix

Let indices of the row and column represent nodes in a graph. If the value at
indice `[i][j]` is some value of `n`, then nodes `[i][j]` and `[j][i]` have `n`
connections in common.

```
0 1 0 1
1 0 1 2
0 1 0 1
1 2 1 0
```

## Incidence Matrix
Let the rows be the index for the node and the index for the column be an edge.
For all nodes in column `[j]`, they are connected if the values are `1`.

```
1 0 1 1 0 0
1 1 0 0 1 1
0 1 1 0 0 0
0 0 1 1 1 1
```
