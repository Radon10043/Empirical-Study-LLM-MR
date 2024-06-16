import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 28: Given the same graph and the same source and destination vertices,
        if we add a new vertex that is only connected to the source vertex, the shortest path length to any other vertex should be the source vertex distance plus the distance from the new vertex to that target vertex."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with an additional vertex connected only to the source
        extended_graph = graph.copy()
        for i in range(len(extended_graph)):
            extended_graph[i].append(0)
        extended_graph.append([0] * len(extended_graph) + [0])
        extended_graph[src][-1] = 1
        extended_graph[-1][dst] = 1

        # Get follow-up output
        follow_out = shortest_path(extended_graph, method=method)

        # Verification
        for target_vertex in range(len(graph)):
            if target_vertex != src:
                self.assertEqual(follow_out[src][target_vertex], source_out[src][target_vertex] + extended_graph[src][-1])


if __name__ == "__main__":
    unittest.main()
