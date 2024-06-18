import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 8: If an edge on the shortest path has its weight increased,
        the new shortest path length should be at least as long as the old one."""
        # Get source output
        matrix, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = matrix[src][dst]

        # Construct follow-up input by finding an edge on the shortest path and increasing its weight
        path_edges = get_shortest_path(predecessors, src, dst)
        if path_edges:
            u, v = path_edges[0]  # a sample edge from the shortest path
            graph[u][v] += 10  # increase the weight of this edge

            # Get follow-up output
            follow_out = shortest_path(graph, method=method)[src][dst]

            # Verification
            self.assertGreaterEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
