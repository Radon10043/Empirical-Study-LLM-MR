import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 4: Adding the same weight to all edges should not change the
        shortest path in an unweighted graph."""
        # Get source output on the unweighted graph
        source_out = shortest_path(graph, unweighted=True, method='D')[src][dst]

        # Construct follow-up input with added weight to all edges
        extra_weight = 10
        follow_graph = list()
        for row in graph:
            new_row = [0 if x == 0 else x + extra_weight for x in row]
            follow_graph.append(new_row)

        # Get folllow-up output on the unweighted graph with added weights
        follow_out = shortest_path(follow_graph, unweighted=True, method='D')[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
