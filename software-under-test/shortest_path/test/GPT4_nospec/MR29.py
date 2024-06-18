import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 29: Tripling the weights of the edges in the graph should not alter the actual shortest path taken, only its total weight."""
        # Get the current shortest path and its total weight
        matrix, predcessors = shortest_path(graph, method=method, return_predecessors=True)
        path = get_shortest_path(predcessors, src, dst)
        weight = matrix[src][dst]

        # Triple the weights of all edges in the graph
        tripled_graph = [[weight * 3 for weight in row] for row in graph]

        # Get the new shortest path and its total weight
        matrix, predcessors = shortest_path(tripled_graph, method=method, return_predecessors=True)
        new_path = get_shortest_path(predcessors, src, dst)
        new_weight = matrix[src][dst]

        # Verify that the shortest path taken is the same, and that its weight is tripled
        self.assertEqual(path, new_path)
        self.assertEqual(weight * 3, new_weight)


if __name__ == "__main__":
    unittest.main()
