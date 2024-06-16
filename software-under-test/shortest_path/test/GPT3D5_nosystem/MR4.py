import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 4: Given the same graph with its predecessor matrix and unweighted=True,
        the shortest path should have the same result as when the unweighted=False."""
        # Get source output with unweighted=True
        source_out_unweighted = shortest_path(graph, method=method, unweighted=True)

        # Get source output with unweighted=False
        source_out_weighted = shortest_path(graph, method=method, unweighted=False)

        # Verification
        self.assertTrue(np.array_equal(source_out_unweighted, source_out_weighted))


if __name__ == "__main__":
    unittest.main()
