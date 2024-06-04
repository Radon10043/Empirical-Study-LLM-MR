import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 3: Given the same graph, the same source and destination vertices,
        but the graph is transposed, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = np.transpose(graph)
        follow_graph = np.ascontiguousarray(follow_graph)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
