import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 6: Adding a shortcut between two non-adjacent nodes on the
        shortest path should not decrease the shortest path length."""
        # Get source output
        matrix, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = matrix[src][dst]

        # Construct follow-up input
        path_nodes = get_shortest_path(predecessors, src, dst)
        for i in range(len(path_nodes) - 2):
            graph[path_nodes[i]][path_nodes[i + 2]] = graph[path_nodes[i]][path_nodes[i + 1]] + graph[path_nodes[i + 1]][path_nodes[i + 2]]

        # Get follow-up output
        follow_out = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
