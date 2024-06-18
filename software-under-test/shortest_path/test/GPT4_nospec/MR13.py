import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 13: Doubling the weight of every edge should not change the path itself, only its cost."""
        # Get source output: both path and cost
        matrix, predcessors = shortest_path(graph, method=method, return_predecessors=True)
        source_cost = matrix[src][dst]
        source_path = get_shortest_path(predcessors, src, dst)

        # Construct follow-up input by doubling the weight of every edge
        double_weight_graph = [[weight * 2 for weight in row] for row in graph]

        # Get follow-up output: both path and cost
        matrix, predcessors = shortest_path(double_weight_graph, method=method, return_predecessors=True)
        follow_cost = matrix[src][dst]
        follow_path = get_shortest_path(predcessors, src, dst)

        # Verification of path
        self.assertEqual(source_path, follow_path)
        # Verification of cost
        self.assertEqual(source_cost * 2, follow_cost)


if __name__ == "__main__":
    unittest.main()
