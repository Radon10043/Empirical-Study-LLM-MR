import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 25: For any two nodes (a, b), and any third node (c), the shortest 
        path from a to b through c should be at least as long as the direct shortest path from a to b."""
        graph = csr_matrix(graph)

        # Compute the shortest direct path from a to b
        direct_path_distance = shortest_path(graph, method=method)[src][dst]

        # Choose a third node
        third_node = self.select_third_node(src, dst, graph.shape[0])

        # Compute the shortest path from a to b through c
        path_a_c = shortest_path(graph, method=method)[src][third_node]
        path_c_b = shortest_path(graph, method=method)[third_node][dst]
        through_c_path_distance = path_a_c + path_c_b

        # Verification
        self.assertLessEqual(direct_path_distance, through_c_path_distance)

    def select_third_node(self, a, b, num_nodes):
        """Selects a third node that's different from the two specified nodes."""
        for node in range(num_nodes):
            if node != a and node != b:
                return node  # Take the first node that's different (could be randomized as well)


if __name__ == "__main__":
    unittest.main()
