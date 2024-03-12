import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 4: If unweighted flag is set to True, changing edge weights to
        1 should yield the same shortest path distances between the same source and destination vertices."""
        # Get source output
        source_out = shortest_path(graph, method=method, unweighted=True)[src][dst]

        follow_graph = list()
        for row in graph:
            follow_graph.append([1 if x > 0 else 0 for x in row])

        # Get folllow-up output
        follow_out = shortest_path(follow_graph, method=method, unweighted=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
