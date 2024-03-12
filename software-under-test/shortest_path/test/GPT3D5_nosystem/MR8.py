import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 8: The shortest path from vertex i to vertex j should be the negation of the shortest path from vertex j to vertex i, in case of undirected graph."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(graph, method=method, directed=False)[dst][src]

        # Verification
        self.assertEqual(source_out, -follow_out)


if __name__ == "__main__":
    unittest.main()
