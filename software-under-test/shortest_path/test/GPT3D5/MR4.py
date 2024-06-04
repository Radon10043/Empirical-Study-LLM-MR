import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 4: Given the same graph, the same source and destination vertices,
        but with the graph converted to an unweighted graph, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = [[1 if x != 0 else 0 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
