import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test2(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 2: Given the same graph, the same source and destination vertices,
        but with the weights negated, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, unweighted=False)[src][dst]

        follow_graph = list()
        for row in graph:
            follow_graph.append([-x for x in row])

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method=method, unweighted=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
