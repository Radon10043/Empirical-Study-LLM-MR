import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: For any two nodes, the shortest path from node A to node B should be the reverse of the shortest path from node B to node A if the graph is undirected."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(graph, method=method, directed=False)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
