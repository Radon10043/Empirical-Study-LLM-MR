import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 19: Increasing the weights of edges not included in the shortest path
        should not affect the distance of that shortest path."""
        # Get the shortest path distances before increasing the weights
        source_matrix, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_dist = source_matrix[src][dst]

        path = get_shortest_path(predecessors, src, dst)

        # Increase the weights of edges not in the shortest path
        if path[1] == dst:
            self.skipTest("Edge is part of a shortest path")
        if graph[src][dst] == 0:
            self.skipTest("Edge does not exist in the graph")
        follow_graph = graph.copy()
        follow_graph[src][dst] += 100

        # Get the distance after increasing the weights
        follow_dist = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_dist, follow_dist)


if __name__ == "__main__":
    unittest.main()
