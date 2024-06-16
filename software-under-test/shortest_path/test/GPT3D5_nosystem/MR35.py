import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 35: Given the same graph, the same source and destination vertices, and if the graph contains a single edge, 
        the shortest path from the source to the destination should be the weight of that edge."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        single_edge_graph = graph.copy()
        single_edge_graph[src][dst] = 1

        # Get follow-up output
        follow_out = shortest_path(single_edge_graph, method=method)

        # Verification
        self.assertTrue(np.allclose(follow_out[src][dst], single_edge_graph[src][dst]))


if __name__ == "__main__":
    unittest.main()