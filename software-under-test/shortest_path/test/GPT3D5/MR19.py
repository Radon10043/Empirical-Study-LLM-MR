import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: Given the same graph, the same source and destination vertices,
        but with the nodes specified for the shortest paths, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, indices=None)[src][dst]

        # Construct follow-up input: specifying nodes for the shortest paths
        indices = [1, 2, 3]  # Example indices
        follow_out = shortest_path(graph, method=method, indices=indices)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
