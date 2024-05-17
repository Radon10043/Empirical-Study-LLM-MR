import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 3: For an undirected graph, the shortest path from a source to a destination
        should be the same as the shortest path from the destination to the source."""
        csgraph = csr_matrix(graph)
        directed = True

        if directed:
            # Get source output
            source_out = shortest_path(csgraph, directed=False)[src][dst]

            # Get follow-up output
            follow_out = shortest_path(csgraph, directed=False)[dst][src]

            # Verification
            self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
