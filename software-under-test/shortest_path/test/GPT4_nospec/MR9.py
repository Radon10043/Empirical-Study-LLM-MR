import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: If a non-existing edge with infinite weight changes to a finite weight,
        the shortest path should be the same or shorter."""
        # Get source output for the shortest path without the finite weight edge
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new edge with finite weight
        max_node = max(src, dst)
        new_edge_weight = 5
        if len(graph) <= max_node + 1:
            for row in graph:
                row.append(float("inf"))  # Extend existing rows with infinite weight
            graph.append([float("inf")] * (max_node + 2))  # Add new row for new node
        graph[src][max_node + 1] = new_edge_weight
        graph[max_node + 1][dst] = new_edge_weight

        # Get follow-up output
        follow_out = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
