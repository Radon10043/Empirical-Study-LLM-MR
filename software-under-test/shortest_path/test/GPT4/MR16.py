import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 16: Connecting all vertices to a new vertex with zero-weighted edges 
        should not affect shortest path calculations in the original graph since zero-weighted edges
        offer no shortcut."""
        directed = choice([True, False])

        # Get source output
        source_out = shortest_path(graph, method=method, directed=directed)

        # Connect all nodes to new node with zero-weighted edge
        extended_graph = graph.copy()
        extended_graph.append([0] * len(extended_graph))
        for i in range(len(extended_graph)):
            extended_graph[i].append(0)

        # Get follow-up output
        follow_out = shortest_path(extended_graph, method=method, directed=directed)

        # Verification
        # Compare only the part of the output matrix that corresponds to the original graph
        self.assertTrue(np.array_equal(source_out, follow_out[:-1, :-1]))


if __name__ == "__main__":
    unittest.main()
