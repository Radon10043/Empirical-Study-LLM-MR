import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 42: Given the same graph, the same source and destination vertices, 
        but adding an additional path between two vertices, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Add an additional path between two vertices
        follow_graph = graph.copy()
        new_vertex = 5
        follow_graph[src][new_vertex] = follow_graph[new_vertex][dst] = 2
        follow_graph[src][dst] = follow_graph[dst][src] = 3

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
