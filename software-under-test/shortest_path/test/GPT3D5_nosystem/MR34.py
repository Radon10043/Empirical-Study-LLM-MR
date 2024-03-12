import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def reverse_edges_on_path(self, graph: list, path: list) -> list:
        """Reverses the direction of the edges on the given path in the graph."""
        new_graph = [row[:] for row in graph]
        for i in range(len(path) - 1):
            new_graph[path[i]][path[i + 1]] = 0
            new_graph[path[i + 1]][path[i]] = graph[path[i]][path[i + 1]]
        return new_graph

    def shortest_path_between_nodes(self, graph: list, method: str, src: int, dst: int) -> list:
        """Returns the shortest path between the source and destination nodes in the graph."""
        _, predecessors = shortest_path(graph, method=method, directed=True, return_predecessors=True)
        path = get_shortest_path(predecessors, src, dst)
        return path

    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 34: Reversing the direction of the edges on the shortest path from A to B should yield the same path from B to A."""
        # Get source output
        path_from_A_to_B = self.shortest_path_between_nodes(graph, method, src, dst)

        reversed_edges_graph = self.reverse_edges_on_path(graph, path_from_A_to_B)

        # Get follow-up output
        path_from_B_to_A = self.shortest_path_between_nodes(reversed_edges_graph, method, dst, src)

        # Verify that the paths are the same
        self.assertEqual(path_from_A_to_B, path_from_B_to_A)


if __name__ == "__main__":
    unittest.main()
