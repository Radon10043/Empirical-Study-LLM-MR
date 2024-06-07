import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 26: Removing a vertex (and its associated edges) that is not on the
        shortest path from src to dst should not affect the distance of the shortest path."""
        graph = csr_matrix(graph)

        # Check that the condition is met: there are vertices not part of the shortest path
        mat, pred_matrix = shortest_path(graph, method=method, return_predecessors=True)
        non_involved_vertex = 1
        path = get_shortest_path(pred_matrix, src, dst)
        if non_involved_vertex in path:
            self.skipTest("Vertex is part of the shortest path")

        # Get source output for the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Remove the vertex and related edges
        graph_minus_vertex = self.remove_vertex_and_edges(graph, non_involved_vertex)

        # Get follow-up output
        new_distance = shortest_path(graph_minus_vertex, method=method)[src][dst]

        # Verification
        self.assertEqual(original_distance, new_distance)

    def remove_vertex_and_edges(self, graph, vertex):
        """Remove the specified vertex and its associated edges from the graph."""
        graph = graph.tolil()  # Assuming graph is in a sparse SciPy format that supports row/column deletion
        graph[vertex, :] = 0  # Remove all outgoing edges from 'vertex'
        graph[:, vertex] = 0  # Remove all incoming edges to 'vertex'
        return graph.tocsr()


if __name__ == "__main__":
    unittest.main()
