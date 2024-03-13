import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 16: Given the same graph, the same source and destination vertices,
        but with the graph modified such that all weights are decreased by a constant value, 
        the shortest path remains the same."""
        constant = 5  # subtraction constant

        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Modify the graph such that all weights are decreased by the constant value
        modified_graph = [[weight - constant for weight in row] for row in graph]

        # Get follow-up output
        _, predecessors = shortest_path(modified_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
