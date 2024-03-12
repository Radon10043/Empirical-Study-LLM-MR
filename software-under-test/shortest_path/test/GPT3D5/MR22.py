import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should follow the same sequence of vertices for the shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method, return_predecessors=True)[1]

        # Construct follow-up input: using a different algorithm
        follow_out = shortest_path(graph, method='D', return_predecessors=True)[1]

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
