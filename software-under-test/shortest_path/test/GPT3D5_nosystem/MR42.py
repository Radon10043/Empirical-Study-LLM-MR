import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def remove_parallel_edges(self, graph: list, src: int, dst: int) -> list:
        """Removes parallel edges between the given source and destination nodes."""
        inf = 99999
        new_graph = [row[:] for row in graph]
        new_graph[src][dst] = inf
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 42: Removing parallel edges between two nodes should not change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        graph_without_parallel_edges = self.remove_parallel_edges(graph, src, dst)

        # Get follow-up output
        follow_out = shortest_path(graph_without_parallel_edges, method=method)

        # Verify that all distances remain the same
        for i in range(len(source_out)):
            for j in range(len(source_out[0])):
                if i != j:
                    self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
