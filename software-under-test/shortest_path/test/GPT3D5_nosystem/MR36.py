import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def modify_edge_on_path(self, graph: list, path: list, new_weight: int) -> list:
        """Modifies the weight of the edges on the given path in the graph."""
        new_graph = [row[:] for row in graph]
        for i in range(len(path) - 1):
            new_graph[path[i]][path[i + 1]] = new_weight
            new_graph[path[i + 1]][path[i]] = new_weight
        return new_graph


    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 36: For undirected graphs, changing an edge weight on a path from A to B should also change the shortest path distance from B to A."""
        dist_matrix, predecessors = shortest_path(graph, method=method, directed=False, return_predecessors=True)
        path_from_A_to_B = get_shortest_path(predecessors, src, dst)

        new_weight = random.randint(1, 1000)
        graph_with_modified_edge = self.modify_edge_on_path(graph, path_from_A_to_B, new_weight)

        # Get the original output
        original_result = dist_matrix

        # Get the follow-up output
        follow_up_result = shortest_path(graph_with_modified_edge, method=method, directed=False)

        # Verify that the distance from B to A has changed after modifying the edge weight
        self.assertNotEqual(original_result[dst][src], follow_up_result[dst][src])


if __name__ == "__main__":
    unittest.main()