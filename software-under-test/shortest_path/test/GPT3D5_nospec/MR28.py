import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 28: Given the same graph, source, and destination vertices,
        if we reverse the direction of a specific edge in the graph,
        the shortest path should be impacted accordingly."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by reversing the direction of a specific edge
        follow_graph = deepcopy(graph)
        tmp = follow_graph[src][dst]
        follow_graph[src][dst] = follow_graph[dst][src]
        follow_graph[dst][src] = tmp

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
