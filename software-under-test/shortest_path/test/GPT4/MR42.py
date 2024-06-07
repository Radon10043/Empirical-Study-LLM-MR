import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 42: After negating all the weights in the graph, the shortest path 
        between any two nodes should still be the same path, but with negated weights."""
        graph = csr_matrix(graph)

        # Assuming the shortest path software can handle negative weights:
        # Get source output for the original graph
        original_distance = shortest_path(graph, method=method)[src][dst]
        original_predecessors = shortest_path(graph, method=method, return_predecessors=True)[1]

        # Negate weights of the graph
        # This step assumes that the graph supports direct negation of its values
        negated_weight_graph = graph.copy()
        negated_weight_graph.data *= -1

        # Get follow-up output for the graph with negated weights
        negated_weight_distance = shortest_path(negated_weight_graph, method=method)[src][dst]
        negated_weight_predecessors = shortest_path(negated_weight_graph, method=method, return_predecessors=True)[1]

        # Extract the path using the predecessors list
        path_original = get_shortest_path(original_predecessors, src, dst)
        path_negated = get_shortest_path(negated_weight_predecessors, src, dst)

        # Verify that the paths are the same
        self.assertEqual(path_original, path_negated)
        # Verify the distances are each other's negation
        self.assertAlmostEqual(original_distance, -negated_weight_distance)


if __name__ == "__main__":
    unittest.main()
