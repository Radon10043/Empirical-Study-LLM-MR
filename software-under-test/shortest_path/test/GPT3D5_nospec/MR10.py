import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 10: Given the same graph, source and destination vertices,
        if all edge weights are doubled but the graph structure remains the same, the shortest path should remain the same."""
        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Construct follow-up input with doubled edge weights
        follow_graph = [[x * 2 for x in row] for row in graph]

        # Get follow-up output
        _, predecessors = shortest_path(follow_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
