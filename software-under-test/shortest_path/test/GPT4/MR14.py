import os, sys
import scipy

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 14: Increasing the weight of a self-loop (e.g., edge from a vertex to itself) 
        should not affect the shortest paths in the graph."""
        # Get source output for all pairs
        source_out = shortest_path(graph, method=method)

        # Increase the weight of the self-loop at src
        updated_graph = graph.copy()
        updated_graph[src][src] += 1

        # Get follow-up output for all pairs
        follow_out = shortest_path(updated_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
