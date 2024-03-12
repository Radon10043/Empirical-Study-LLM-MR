import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 17: Given the same graph, the same source and destination vertices,
        but with the graph representing an undirected graph, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        # Construct follow-up input: representing an undirected graph
        follow_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
