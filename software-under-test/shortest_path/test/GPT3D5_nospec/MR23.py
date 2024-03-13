import random
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1))
    def test23(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 23: Given the same graph, the same source and destination vertices, 
        but with some of the edges in the graph having their weights multiplied by -1, 
        the shortest path should remain the same."""
        # Modify the weights of a subset of edges by multiplying them with -1
        modified_graph = [[weight * -1 if random.random() < 0.3 else weight for weight in row] for row in graph]

        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Get follow-up output
        _, predecessors = shortest_path(modified_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
