import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Duplicating edges with the same weight does not change 
        the shortest path distances."""
        # Get source output for the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Duplicate all edges with the same weight
        duplicated_edges_graph = self.duplicate_edges(graph)

        # Get follow-up output after duplicating edges
        duplicated_edges_distance = shortest_path(duplicated_edges_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_distance, duplicated_edges_distance)

    def duplicate_edges(self, graph):
        """Duplicate all non-zero edges in the graph while keeping the weights the same."""
        graph_with_duplicated_edges = graph.copy()
        graph_with_duplicated_edges += graph._with_data(lambda x: x, copy=True)
        return graph_with_duplicated_edges


if __name__ == "__main__":
    unittest.main()
