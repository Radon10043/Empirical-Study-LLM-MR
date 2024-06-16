import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 14: Given the same graph, the same source and destination vertices, 
        and the same algorithm, if the graph is sparse, and then densified, 
        the shortest path lengths should remain the same."""
        # Get source output with sparse graph
        source_out_sparse = shortest_path(graph, method=method)

        # Convert sparse graph to dense graph
        dense_graph = convert_sparse_to_dense(graph)

        # Get follow-up output with dense graph
        follow_out_dense = shortest_path(dense_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out_sparse, follow_out_dense))


if __name__ == "__main__":
    unittest.main()