import scipy
from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(load_test_cases)
    def test8(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 8: Given the same graph, the same source and destination vertices,
        but with different starting methods leading to the same method, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_method = "auto" if method == "FW" else "FW"
        # Convert the list to a sparse matrix
        sparse_graph = scipy.sparse.csr_matrix(graph)
        follow_out = shortest_path(sparse_graph, method=follow_method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)

if __name__ == "__main__":
    unittest.main()
