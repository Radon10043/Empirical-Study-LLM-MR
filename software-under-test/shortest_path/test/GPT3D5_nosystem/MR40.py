import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def reverse_edge_weights(self, graph: list) -> list:
        """Reverses the edge weights in the graph."""
        new_graph = [row[:] for row in graph]
        for i in range(len(graph)):
            for j in range(len(graph[i])):
                if graph[i][j] != 0:
                    new_graph[i][j] = 1 / graph[i][j]
        return new_graph

    def inverse_of_distances(self, distances: list) -> list:
        """Returns the inverse of the distances in the given list."""
        return [[1 / distances[i][j] if i != j else 0 for j in range(len(distances[i]))] for i in range(len(distances))]

    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 40: Reversing the edge weights and then finding the inverse of the distances should yield the same result as finding the distances directly."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        reverse_edge_weights_graph = self.reverse_edge_weights(graph)

        # Get follow-up output
        follow_out = self.inverse_of_distances(shortest_path(reverse_edge_weights_graph, method=method))

        # Verify that the distances are the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                self.assertAlmostEqual(source_out[i][j], follow_out[i][j], delta=1e-7)


if __name__ == "__main__":
    unittest.main()
