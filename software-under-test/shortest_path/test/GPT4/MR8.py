import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 8: If an edge weight is reduced and all other edge weights are unchanged, 
        then the shortest path cannot be increased."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Reduce the weight of an edge for follow-up input
        reduced_weight_graph = graph.copy()
        for i in range(len(reduced_weight_graph)):
            for j in range(len(reduced_weight_graph[i])):
                if reduced_weight_graph[i][j] > 1:
                    reduced_weight_graph[i][j] -= 1

        # Get follow-up output
        follow_out = shortest_path(reduced_weight_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
