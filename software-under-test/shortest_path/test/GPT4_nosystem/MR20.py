import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 20: Inverting the weights of the graph (e.g., new_weight = 1/weight for
        weighted graphs) should change the ordering of the shortest paths based on inverted weights."""
        # Invert weights of the graph
        inverted_weight_graph = [[1./x if x != 0 else 0 for x in row] for row in graph]

        # Get distance matrices based on inverted weights
        _, source_pred = shortest_path(graph, method=method, return_predecessors=True)
        _, follow_pred = shortest_path(inverted_weight_graph, method=method, return_predecessors=True)

        # Verify that paths have different orderings
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i == j:
                    continue
                self.assertNotEqual(get_shortest_path(source_pred, i, j), get_shortest_path(follow_pred, i, j))


if __name__ == "__main__":
    unittest.main()
