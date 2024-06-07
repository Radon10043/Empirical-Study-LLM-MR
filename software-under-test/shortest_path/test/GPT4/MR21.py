import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 21: If we convert a directed graph to its equivalent undirected version 
        by symmetrizing it, the shortest path in the undirected graph should be less than or equal to 
        the directed version."""
        # Get source output for the directed graph
        directed_distance = shortest_path(graph, method=method, directed=True)[src][dst]

        # Create an equivalent undirected graph by symmetrizing it
        undirected_graph = graph.copy()
        for i in range(len(undirected_graph)):
            for j in range(i, len(undirected_graph)):
                undirected_graph[j][i] = undirected_graph[i][j]

        # Get follow-up output with undirected graph
        undirected_distance = shortest_path(undirected_graph, method=method, directed=False)[src][dst]

        # Verification: the shortest path in the undirected graph should be shorter or equal
        self.assertLessEqual(undirected_distance, directed_distance)


if __name__ == "__main__":
    unittest.main()
