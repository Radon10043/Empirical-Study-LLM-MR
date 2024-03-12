import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def reverse_all_edges(self, graph: list) -> list:
        """Reverses the direction of all edges in the graph."""
        new_graph = [[0 for _ in range(len(graph))] for _ in range(len(graph))]
        for i in range(len(graph)):
            for j in range(len(graph)):
                if graph[i][j] != 0:
                    new_graph[j][i] = graph[i][j]
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 33: Reversing the direction of all edges in the graph should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        new_graph = self.reverse_all_edges(graph)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == '__main__':
    unittest.main()