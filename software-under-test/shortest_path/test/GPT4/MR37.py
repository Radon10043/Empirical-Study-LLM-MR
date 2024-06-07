import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 37: If all weights are multiplied by a positive constant, the shortest path 
        should be the same but scaled by that constant."""
        graph = csr_matrix(graph)

        scaling_factor = 2
        # Get the original shortest path
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Scale all weights by a positive constant
        scaled_graph = graph * scaling_factor

        # Get shortest path in scaled graph
        scaled_distance = shortest_path(scaled_graph, method=method)[src][dst]

        # Verify scaled distance is equal to the original distance multiplied by the scaling factor
        self.assertEqual(scaled_distance, original_distance * scaling_factor)


if __name__ == "__main__":
    unittest.main()
