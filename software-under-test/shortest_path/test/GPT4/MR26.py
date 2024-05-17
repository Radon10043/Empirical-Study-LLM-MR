import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 26: Adding disconnected nodes (zero-weight edges to all other nodes) to the graph 
        should not affect the shortest path between the existing nodes."""
        csgraph = csr_matrix(graph)

        # Add additional disconnected nodes to the graph
        num_additional_nodes = 2
        original_num_nodes = csgraph.shape[0]
        modified_csgraph = csr_matrix(
            (original_num_nodes + num_additional_nodes, original_num_nodes + num_additional_nodes)
        )
        modified_csgraph[:original_num_nodes, :original_num_nodes] = csgraph

        # Compute shortest paths before and after addition of nodes
        original_paths = shortest_path(csgraph)
        modified_paths = shortest_path(modified_csgraph)

        # Shortest paths among original nodes should remain unaffected by addition of disconnected nodes
        np.testing.assert_array_equal(original_paths, modified_paths[:original_num_nodes, :original_num_nodes])


if __name__ == "__main__":
    unittest.main()
