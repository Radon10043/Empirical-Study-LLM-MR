import os, sys
import scipy

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 14: Adding a new vertex that does not decrease the distance of existing
        shortest paths should not affect the shortest paths between existing vertices."""
        # Get source output
        source_out = shortest_path(csr_matrix(graph))

        # Add a new vertex to the graph that does not decrease the distance of existing shortest paths
        num_v = len(graph)
        row = [99999] * (num_v + 1)
        follow_graph = graph.copy()
        for row in follow_graph:
            row.append(99999)
        follow_graph.append(row)

        # Get follow-up output
        follow_out = shortest_path(csr_matrix(follow_graph))
        for i in range(num_v):
            for j in range(num_v):
                self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
