import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 34: Given the same graph and vertices, if the weights of all edges are decreased by a constant value,
        the shortest path should remain the same."""
        constant = 5  # subtraction constant

        # Get the original shortest path
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Decrease the weights of all edges by the constant value
        modified_graph = [[weight - constant for weight in row] for row in graph]

        # Get the shortest path in the modified graph
        _, predecessors = shortest_path(modified_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
