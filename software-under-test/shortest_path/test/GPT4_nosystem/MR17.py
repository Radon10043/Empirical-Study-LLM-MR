import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test17(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 17: Adding a new vertex with edges to existing vertices should not
        reduce the shortest path distances among the original vertices."""
        # Extend the graph with a new node
        new_graph = deepcopy(graph)
        for row in new_graph:
            row.append(randint(1, 100))
        new_graph.append([randint(1, 100) for _ in range(len(graph) + 1)])

        # Get original distances
        original_dist_matrix = shortest_path(graph, method=method)

        # Get new distances with the extra node
        new_dist_matrix = shortest_path(new_graph, method=method)

        # Verify that shortest paths among original vertices have not been shortened
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertLessEqual(original_dist_matrix[i][j], new_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
