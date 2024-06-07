import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 18: Concatenating two paths to form a third path should result in 
        a distance that is at least the distance of the longest single path (Triangle Inequality)."""
        # Select an intermediate node that is different from src and dst
        intermediate_node = 1
        if src == intermediate_node or dst == intermediate_node:
            self.skipTest("Intermediate node is the same as src or dst")

        # Compute the shortest paths
        src_to_intermediate = shortest_path(graph, method=method)[src][intermediate_node]
        intermediate_to_dst = shortest_path(graph, method=method)[intermediate_node][dst]

        concatenated_path_distance = src_to_intermediate + intermediate_to_dst

        # The shortest distance from src to dst can't be longer than the concatenated path
        shortest_distance = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(shortest_distance, concatenated_path_distance)


if __name__ == "__main__":
    unittest.main()
