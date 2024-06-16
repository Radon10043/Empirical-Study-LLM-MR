import os, sys

from random import shuffle

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: Given the same graph, the same source and destination vertices,
        and return_predecessors=True, the predecessor matrix should be symmetric."""
        # Get source output with return_predecessors=True
        source_out, source_predecessors = shortest_path(graph, method=method, return_predecessors=True)

        # Verification
        self.assertTrue(np.array_equal(source_predecessors, np.transpose(source_predecessors)))


if __name__ == "__main__":
    unittest.main()
