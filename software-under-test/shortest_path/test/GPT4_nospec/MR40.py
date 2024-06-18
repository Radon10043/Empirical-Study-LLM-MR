import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 40: If every edge weight in the graph is increased by a fixed additive amount, 
        the shortest path should stay the same, but its total weight will increase by the number of edges in the path multiplied by the additive amount."""
        # Get the shortest path with its actual path nodes (assuming such a function exists)
        matrix, predcessors = shortest_path(graph, method=method)
        path_nodes = get_shortest_path(predcessors, src, dst)
        original_weight = matrix[src][dst]

        # Increase every edge weight by a fixed amount (e.g., 5)
        additive_amount = 5
        increased_weight_graph = [[weight+additive_amount if weight != float('inf') else weight for weight in row] for row in graph]

        # Get the new shortest path with its total weight
        matrix, predcessors = shortest_path(increased_weight_graph, method=method)
        new_path_nodes = get_shortest_path(predcessors, src, dst)
        new_weight = matrix[src][dst]

        # Calculate the expected new total weight
        expected_new_weight = original_weight + additive_amount * (len(path_nodes) - 1)

        # Verify that the shortest path is the same and that the total weight matches the expected new weight
        self.assertEqual(path_nodes, new_path_nodes)
        self.assertEqual(new_weight, expected_new_weight)

if __name__ == "__main__":
    unittest.main()
