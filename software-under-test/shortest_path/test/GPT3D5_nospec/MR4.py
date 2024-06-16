import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 4: Given the same graph, the same source, and destination vertices,
        but with an additional intermediate vertex added, the shortest path should be shortest
        from source to intermediate vertex combined with shortest from intermediate to destination."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with an additional intermediate vertex
        follow_graph = graph.copy()
        for i in range(len(graph)):
            follow_graph[i].append(float("inf"))

        follow_graph.append([float("inf") for _ in range(len(graph) + 1)])  # Add a row for the new vertex

        # Get follow-up output
        matrix = shortest_path(follow_graph, method=method)

        # Verification
        self.assertEqual(source_out, matrix[src][len(graph)] + matrix[len(graph)][dst])


if __name__ == "__main__":
    unittest.main()
