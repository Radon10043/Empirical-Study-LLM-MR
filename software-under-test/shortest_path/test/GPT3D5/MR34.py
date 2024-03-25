import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: Given the same graph and vertices, the output of the shortest path should remain the same if
        the same graph is represented using a different mutable data structure with the exact same elements."""
        from scipy.sparse import csr_matrix

        # Get source output using a list representation of the graph
        source_out_list = shortest_path(graph, method=method)[src][dst]

        # Convert the graph to a different mutable data structure
        follow_graph = csr_matrix(graph)

        # Get follow-up output using the converted data structure
        follow_out_dd = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_list, follow_out_dd)


if __name__ == "__main__":
    unittest.main()
