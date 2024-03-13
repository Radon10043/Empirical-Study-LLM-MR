import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 22: Given the same graph, the same source and destination vertices, 
        but with the weights in the graph modified by a function (e.g., squared), the shortest path remains the same."""
        # Define a function to modify the weights
        def modify_weight(weight):
            return weight ** 2

        # Modify the weights in the graph using the defined function
        modified_graph = [[modify_weight(weight) for weight in row] for row in graph]

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
