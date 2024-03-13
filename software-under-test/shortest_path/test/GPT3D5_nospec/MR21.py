import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 21: Given the same graph, the same source and destination vertices, 
        but with all weights set to the same value, the shortest path should not change."""
        # Set all weights in the graph to the same value
        same_weight_graph = [[10 for _ in range(len(graph))] for _ in range(len(graph))]

        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Get follow-up output
        _, predecessors = shortest_path(same_weight_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
