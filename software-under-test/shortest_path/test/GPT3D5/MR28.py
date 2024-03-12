import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Given the same graph and vertices, the output of the shortest path should remain the same if
        the graph is represented using a different storage type (e.g., list of lists vs. NumPy array)."""
        import numpy as np

        # Get source output using list of lists
        source_out_list = shortest_path(graph, method=method)[src][dst]

        # Convert the graph to a NumPy array
        np_graph = np.array(graph)

        # Get follow-up output using NumPy array
        follow_out_np = shortest_path(np_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_list, follow_out_np)


if __name__ == "__main__":
    unittest.main()
