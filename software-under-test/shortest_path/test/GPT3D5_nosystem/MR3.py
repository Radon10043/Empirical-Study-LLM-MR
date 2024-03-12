import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 3: If the graph is directed, reversing the direction of the edges
        should yield the same shortest path distance between the same source and destination vertices."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
