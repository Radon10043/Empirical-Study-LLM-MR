import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 13: Removing an edge that is not part of any shortest paths between 
        any pairs of nodes should not affect the shortest path distance"""
        # Get source output for all pairs
        original_distances, predecessors = shortest_path(graph, method=method, return_predecessors=True)

        path = get_shortest_path(predecessors, src, dst)
        if path[1] == dst:
            self.skipTest("Edge is part of a shortest path")
        if graph[src][dst] == 0:
            self.skipTest("Edge does not exist in the graph")

        # Remove a non-critical edge (not part of any shortest path) from the graph
        updated_graph = graph.copy()
        updated_graph[src][dst] = 0

        # Get follow-up output for all pairs
        updated_distances = shortest_path(updated_graph, method=method)

        # Verification: shortest paths should be the same for all vertices except where the edge was removed
        self.assertTrue(np.allclose(np.delete(original_distances, dst, axis=1), np.delete(updated_distances, dst, axis=1)))


if __name__ == "__main__":
    unittest.main()
