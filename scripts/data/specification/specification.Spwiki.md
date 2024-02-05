> ### `shortest_path` Function Specification
>
> #### Description
> The `shortest_path` function calculates the shortest path distance between a source vertex (src) and a destination vertex (dst) in an undirected graph. The graph is represented by a collection of edges, where each edge is a vector of three integers: the start vertex, the end vertex, and the weight of the edge. The function implements Dijkstra's algorithm to find the shortest path.
>
> #### Function Signatures
> ```c++
> int shortest_path(vector<vector<int>> edges, int src, int dst, int n);
> ```
>
> #### Parameters
> - `edges`: A `vector<vector<int>>` representing the collection of edges in the graph. Each edge is represented by a vector containing three integers `[start vertex, end vertex, weight]`.
> - `src`: An `int` representing the source vertex from which to calculate the shortest path.
> - `dst`: An `int` representing the destination vertex to which the shortest path distance is calculated.
> - `n`: An `int` representing the total number of vertices in the graph.
>
> #### Returns
> - `int`: The shortest distance from the source vertex (`src`) to the destination vertex (`dst`). If there is no path between `src` and `dst`, the behavior is dependent on the implementation details.
>
> #### Helper Function: `Dijkstra`
> - **Description**: Implements Dijkstra's algorithm to find the shortest path distances from a given source vertex to all other vertices in the graph.
> - **Signature**: `int* Dijkstra(int matrix[][100], int source, int vertex_num)`
> - **Parameters**:
>     - `matrix`: A 2D array of integers representing the adjacency matrix of the graph. `matrix[i][j]` represents the weight of the edge between vertices `i` and `j`. If there is no edge, the weight is considered `INT_MAX`.
>     - `source`: The source vertex.
>     - `vertex_num`: The number of vertices in the graph.
> - **Returns**: A pointer to an array of integers where the `i`th element represents the shortest distance from the source vertex to vertex `i`.
>
> #### Logic
> 1. **Graph Initialization**: Initializes a 2D array `matrix` to represent the graph's adjacency matrix, setting all distances to `INT_MAX` initially. Then, updates `matrix` with the edges' weights provided in the `edges` parameter.
> 2. **Dijkstra's Algorithm**: Calls the `Dijkstra` function to compute the shortest path distances from the source vertex to all other vertices.
> 3. **Return Shortest Path to Destination**: Returns the distance from the source vertex to the destination vertex as found in the array returned by `Dijkstra`.
>
> #### Notes
> - This implementation assumes that the graph does not contain any negative weight cycles.
> - The `Dijkstra` function uses a fixed-size array for simplicity, which limits the number of vertices to 100. For larger graphs, modifications to the code would be required.
> - The adjacency matrix representation may not be efficient for sparse graphs. In such cases, an adjacency list representation might be preferred.