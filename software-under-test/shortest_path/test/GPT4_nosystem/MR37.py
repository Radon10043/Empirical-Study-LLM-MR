import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test37(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 37: If an alternative path from a source to destination goes 
        through an intermediate node k and if an edge directly connecting the source to the intermediate
        node k is added with a weight less than the shortest path from the source to k, then the 
        shortest path from the source to destination should not increase."""
        # Pick a source and destination with an intermediate node k guaranteed not to be directly connected to the source
        # This requires that the source and k are not the same and an edge from source to k is not in graph
        # Original shortest paths
        original_dist_matrix, pred = shortest_path(graph, method=method, return_predecessors=True)

        path = get_shortest_path(pred, src, dst)
        if len(path) < 3:
            self.skipTest("Source and destination are directly connected, no intermediate node to test")
        k = path[1]

        # Add an edge from the source to intermediate node k with a lower weight than the current shortest path
        new_edge = 1
        new_graph = deepcopy(graph)
        new_graph[src][k] = new_edge

        # Shortest paths with the new graph
        new_dist_matrix = shortest_path(new_graph, method=method)

        # Verify the shortest path from source to destination is the same or reduced
        self.assertLessEqual(new_dist_matrix[src][dst], original_dist_matrix[src][dst])


if __name__ == "__main__":
    unittest.main()
