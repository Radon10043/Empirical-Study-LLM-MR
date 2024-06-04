import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Given the same graph, the same source and destination vertices,
        but with weights of edges changed to 1, the output should remain the same for all pairs of vertices."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify the graph to have all edge weights as 1
        follow_graph = [[1 if x != 0 else 0 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
