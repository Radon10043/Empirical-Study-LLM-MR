import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 3: Given the same graph with reversed direction edges,
        the shortest path from source to destination should be the reverse of the original shortest path."""
        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_path = get_shortest_path(predecessors, src, dst)

        # Construct follow-up input with reversed direction edges
        follow_graph = []
        for row in graph:
            follow_graph.append(row[::-1])

        # Get follow-up output
        _, predecessors = shortest_path(follow_graph, method=method, return_predecessors=True)
        follow_path = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_path, list(reversed(follow_path)))


if __name__ == "__main__":
    unittest.main()
