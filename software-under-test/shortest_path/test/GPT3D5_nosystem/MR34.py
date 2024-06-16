import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: Given the same graph, the same source and destination vertices, 
        if we reverse the direction of all edges in the graph and then find the shortest path, 
        the distance in the reversed graph should be the same as the original graph."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with reversed edges
        reversed_graph = np.transpose(graph)
        reversed_graph = np.ascontiguousarray(reversed_graph)

        # Get follow-up output
        follow_out = shortest_path(reversed_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
