import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 36: Given the same graph, source and destination vertices,
        if we multiply the weights of all edges by -1, 
        the shortest path should be the same as the original shortest path."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by multiplying the weights of all edges by -1
        negated_weights_graph = [[-1 * x for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(negated_weights_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
