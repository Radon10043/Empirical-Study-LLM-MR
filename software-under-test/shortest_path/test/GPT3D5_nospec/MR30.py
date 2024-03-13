import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Given the same graph and vertices, if the weights of all edges are multiplied by -1, 
        the shortest path remains the same."""
        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Multiply all edge weights by -1
        negated_graph = [[-weight for weight in row] for row in graph]

        # Get the shortest path in the negated graph
        negated_shortest_path = shortest_path(negated_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, negated_shortest_path)


if __name__ == "__main__":
    unittest.main()
