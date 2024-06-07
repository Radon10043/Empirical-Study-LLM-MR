import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 17: For each pair of nodes (src, dst), the shortest_path output 
        must be symmetric if the graph is undirected."""
        # Compute the shortest path in the undirected version of the graph
        undirected_graph = graph.copy()
        for i in range(len(undirected_graph)):
            for j in range(i, len(undirected_graph)):
                undirected_graph[j][i] = undirected_graph[i][j]

        # Get source output and follow-up output in reverse
        source_out = shortest_path(undirected_graph, method=method, directed=False)[src][dst]
        follow_out = shortest_path(undirected_graph, method=method, directed=False)[dst][src]

        # Verification: the outputs must be the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
