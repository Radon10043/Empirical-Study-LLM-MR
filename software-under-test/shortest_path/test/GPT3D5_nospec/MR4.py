import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 4: Given the same graph with an added vertex, the output should be the same as the original graph."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Adding an extra vertex with large weights
        modified_graph = graph.copy()
        inf = 99999
        for row in modified_graph:
            row.append(inf)
        modified_graph.append([inf] * (len(modified_graph) + 1))
        modified_graph[-1][-1] = 0

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
