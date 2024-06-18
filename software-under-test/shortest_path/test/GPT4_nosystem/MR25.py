import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str):    # Fixed
        """Metamorphic Relation 25: Adding a set of additional edges that do not create new
        shorter paths than the existing shortest paths should not change the shortest path
        distances in the original graph."""
        # Perform the original shortest path computation
        original_dist_matrix = shortest_path(graph, method=method)

        # Add additional edges to the graph without creating shorter paths
        follow_graph = deepcopy(graph)
        for i in range(len(follow_graph)):
            for j in range(len(follow_graph)):
                if i != j and follow_graph[i][j] == 0:
                    follow_graph[i][j] = 1e6

        # Compute shortest paths again with the additional edges
        new_dist_matrix = shortest_path(follow_graph, method=method)

        # The shortest path distances should remain unchanged
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(original_dist_matrix[i][j], new_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
