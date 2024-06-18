import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 9: If a non-existing edge with infinite weight changes to a finite weight,
        the shortest path should be the same or shorter."""
        # Get source output for the shortest path without the finite weight edge
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new edge with finite weight
        new_edge_weight = 5
        for i in range(len(graph)):
            has_add = False
            for j in range(len(graph)):
                if graph[i][j] == float("inf"):
                    graph[i][j] = new_edge_weight
                    has_add = True
                    break
            if has_add:
                break

        # Get follow-up output
        follow_out = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
