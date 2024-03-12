import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 23: Given the same graph and vertices, the output should be the same irrespective of whether the input is unweighted or weighted."""
        # Get source output with weighted input graph
        source_weighted = shortest_path(graph, method=method, unweighted=False)[src][dst]

        # Get source output with unweighted input graph
        source_unweighted = shortest_path(graph, method=method, unweighted=True)[src][dst]

        # Verification
        self.assertEqual(source_weighted, source_unweighted)


if __name__ == "__main__":
    unittest.main()
