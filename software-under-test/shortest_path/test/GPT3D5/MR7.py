import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph, the same source and destination vertices,
        but with the graph where all edge weights are added by a constant C, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        constant_c = 5
        follow_graph = [[x + constant_c for x in row] for row in graph]
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
