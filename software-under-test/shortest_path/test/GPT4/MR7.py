import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 7: Doubling the weights of all edges in the graph should result in 
        the shortest path being doubled as well."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Double the weights of all edges in the graph for follow-up input
        double_weight_graph = graph.copy()
        for i in range(len(double_weight_graph)):
            for j in range(len(double_weight_graph[i])):
                double_weight_graph[i][j] *= 2

        # Get follow-up output
        follow_out = shortest_path(double_weight_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out * 2, follow_out)


if __name__ == "__main__":
    unittest.main()
