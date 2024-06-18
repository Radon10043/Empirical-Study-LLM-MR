import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Introducing additional edges with infinite weight should not change the shortest path."""
        # Calculate the shortest path from src to dst
        shortest_path_before = shortest_path(graph, method=method)[src][dst]

        # Introduce new edges with infinite weight to the graph matrix
        augmented_graph = [[weight if i != j else float("inf") for j, weight in enumerate(row)] for i, row in enumerate(graph)]

        # Calculate the shortest path after introducing infinite weight edges
        shortest_path_after = shortest_path(augmented_graph, method=method)[src][dst]

        # The introduction of infinitive weight edges should not affect the previous shortest path length
        self.assertEqual(shortest_path_before, shortest_path_after)


if __name__ == "__main__":
    unittest.main()
