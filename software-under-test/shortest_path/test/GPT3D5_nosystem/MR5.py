import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 5: Given the same graph and the same source and destination vertices,
        the shortest path from i to j should be the reverse of the shortest path from j to i."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Get follow-up output from j to i
        follow_out = shortest_path(graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, np.transpose(follow_out)))


if __name__ == "__main__":
    unittest.main()
