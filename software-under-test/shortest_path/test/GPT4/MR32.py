import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Increasing the weights of all edges equally should not change the
        path taken for the shortest path, only the total weight of the path itself."""
        graph = csr_matrix(graph)

        # Get source output for the original graph
        original_distance, original_predecessors = shortest_path(graph, method=method, directed=True, return_predecessors=True)
        original_path = get_shortest_path(original_predecessors, src, dst)

        # Increase the weight of all edges by a constant value
        constant_increase = 5
        graph_with_increased_weights = graph + (graph != 0) * constant_increase

        # Get follow-up output for the graph with increased edge weights
        increased_weight_distance, increased_weight_predecessors = shortest_path(graph_with_increased_weights, method=method, directed=True, return_predecessors=True)
        increased_weight_path = get_shortest_path(increased_weight_predecessors, src, dst)

        # Verify that the paths remain the same
        self.assertEqual(original_path, increased_weight_path)
        # Verify that the distance of the path has increased by the amount equal to the path length
        # multiplied by the constant
        path_length = len(original_path) - 1  # Exclude the source itself
        expected_increase = constant_increase * path_length
        self.assertEqual(original_distance + expected_increase, increased_weight_distance)


if __name__ == "__main__":
    unittest.main()
