import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 17: When two unconnected components in a graph are joined by a single edge, 
        the shortest path between nodes from different components must pass through the edge connecting them."""
        # Assume csgraph consists of two unconnected components and join_edge is the edge connecting them.
        join_edge = connect_components(graph)  # Assume this function exists and returns a tuple (i, j)

        connected_csgraph = graph.copy()
        connected_csgraph[join_edge] = 5  # An arbitrary non-zero weight for the new edge
        connected_csgraph = csr_matrix(connected_csgraph)  # Sparse representation

        # Original shortest paths and predecessors
        original_dists, _ = shortest_path(graph, return_predecessors=True)

        # Shortest paths and predecessors after adding a connecting edge
        connected_dists, connected_preds = shortest_path(connected_csgraph, return_predecessors=True)

        num_vertices = original_dists.shape[0]

        # Verification
        for i in range(num_vertices):
            for j in range(num_vertices):
                # Skip if vertices are in the same component or one of them is the vertex in the join_edge
                if i == join_edge[0] or j == join_edge[0] or i == join_edge[1] or j == join_edge[1] or original_dists[i, j] != np.inf:
                    continue

                # Reconstruct the path
                path = []
                cur = j
                while cur != -9999:  # Assuming -9999 indicates no predecessor
                    path.insert(0, cur)
                    cur = connected_preds[i, cur]

                # Ensure the join edge is in the path
                self.assertIn(join_edge[0], path)
                self.assertIn(join_edge[1], path)


if __name__ == "__main__":
    unittest.main()
