import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 42: Reflecting a graph (swapping edge weights between (i, j) and (j, i))
        should result in the same shortest path lengths since the graph topology remains identical."""
        reflected_graph = deepcopy(graph)
        size = len(graph)
        # Swap the weights between (i, j) and (j, i)
        for i in range(size):
            for j in range(i+1, size):
                reflected_graph[i][j], reflected_graph[j][i] = reflected_graph[j][i], reflected_graph[i][j]

        # Obtain shortest path distances for both graphs
        original_dist_matrix = shortest_path(graph, method=method)
        reflected_dist_matrix = shortest_path(reflected_graph, method=method)

        # Check if distances remain unchanged since only the directionality has been altered
        for i in range(size):
            for j in range(size):
                self.assertEqual(original_dist_matrix[i][j], reflected_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
