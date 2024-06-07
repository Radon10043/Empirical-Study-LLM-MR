import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 10: Adding a new vertex and edges that do not provide a new shorter path should not change the shortest path."""
        directed = choice([True, False])

        # Get source output
        source_out = shortest_path(graph, method=method, directed=directed)[src][dst]

        # Add a new vertex and edges that do not create a shorter path between src and dst
        extended_graph = graph.copy()
        extended_graph.append([0] * len(extended_graph))
        for i in range(len(extended_graph)):
            extended_graph[i].append(0)

        # Get follow-up output
        follow_out = shortest_path(extended_graph, method=method, directed=directed)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
