import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Given the same graph, source and destination vertices,
        if we double the weight of all edges in the graph, 
        the shortest path should also be doubled."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by doubling the weight of all edges
        follow_graph = [[x * 2 for x in row] for row in graph]

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(modified_shortest_path, original_shortest_path * 2)


if __name__ == "__main__":
    unittest.main()
