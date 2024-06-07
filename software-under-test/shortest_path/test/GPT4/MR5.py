import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 5: If edges' weights are incremented by a constant factor, the shortest
        path distance should also be incremented by the same factor for an unweighted graph turned weighted."""
        # Get source output from an unweighted graph
        source_out = shortest_path(graph, method=method, unweighted=True)[src][dst]

        add_weight = 3
        # Create a weighted graph by adding a constant weight to unweighted edges
        weighted_graph = graph.copy()
        for r in range(len(weighted_graph)):
            for c in range(len(weighted_graph)):
                if weighted_graph[r][c] != 0:
                    weighted_graph[r][c] += add_weight

        # Get follow-up output
        follow_out = shortest_path(weighted_graph, method=method, unweighted=False)[src][dst]

        # Verification
        self.assertEqual(source_out + add_weight, follow_out)


if __name__ == "__main__":
    unittest.main()
