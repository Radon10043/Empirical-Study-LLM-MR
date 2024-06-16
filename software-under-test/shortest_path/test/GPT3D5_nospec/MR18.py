import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 18: Given a directed graph, the shortest path from source to destination should be the reverse 
        of the shortest path obtained by reversing the direction of all edges in the graph."""
        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Construct follow-up input by reversing the direction of all edges in the graph
        reversed_graph = graph.copy()
        reversed_graph = np.transpose(reversed_graph)
        reversed_graph = np.ascontiguousarray(reversed_graph)

        # Get follow-up output
        _, predecessors = shortest_path(reversed_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, dst, src)

        # Verification
        self.assertEqual(source_out, list(reversed(follow_out)))


if __name__ == "__main__":
    unittest.main()
