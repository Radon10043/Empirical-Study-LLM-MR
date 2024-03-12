import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):

    def add_cycle_to_graph(self, graph: list, node: int) -> list:
        """Adds a cycle to the graph using the given node."""
        new_graph = graph.copy()
        new_graph[node][node] = random.randint(1, 1000)
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 39: Adding a cycle to the graph should not change the shortest path distances between nodes not in the cycle."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        node = random.randint(0, len(graph) - 1)
        graph_with_cycle = self.add_cycle_to_graph(graph, node)

        # Get follow-up output
        follow_out = shortest_path(graph_with_cycle, method=method)

        # Verify that the distances remain the same for nodes not in the cycle
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()