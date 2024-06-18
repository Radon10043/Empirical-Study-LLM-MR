import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 11: Doubling the weight of all edges should not change the order of
        shortest paths, but the distance of the shortest paths should also double."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Doubles the weight of all edges
        doubled_graph = [[x * 2 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(doubled_graph, method=method)

        # Verification that distances have doubled
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(source_out[i][j] * 2, follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
