import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test41(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 41: Given the same graph and vertices, if the weights of all edges are set to a negative value,
        the shortest path results should remain the same."""
        # Set all edge weights to a negative value
        negative_graph = [[-1 for _ in row] for row in graph]

        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        _, predecessors = shortest_path(negative_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verify the shortest path results
        self.assertListEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
