import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 36: For any two non-zero edges in a cycle, reducing the weight of
        one while increasing the weight of the other by the same amount should result in the same
        or greater shortest path that involves this cycle."""
        # Identify a cycle and modify two non-zero edges with equal but opposite weight changes
        # This requires previous knowledge of the cycle in the graph, which might be informed by the test case setup.
        # Assume cycle_edges is a list of tuples (i, j) that forms a cycle and is provided by the test case
        cycle_edges = []

        delta = 5
        decrease_edge = cycle_edges[0]
        increase_edge = cycle_edges[-1]

        modified_graph = deepcopy(graph)
        modified_graph[decrease_edge[0]][decrease_edge[1]] -= delta
        modified_graph[increase_edge[0]][increase_edge[1]] += delta

        # Compute shortest paths before and after the modification
        original_dist_matrix = shortest_path(graph, method=method)
        modified_dist_matrix = shortest_path(modified_graph, method=method)

        # Verify the distances are the same or have increased for paths involving the modified edges
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertLessEqual(original_dist_matrix[i][j], modified_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
