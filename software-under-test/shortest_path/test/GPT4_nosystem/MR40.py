import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 40: Removing all edges going out from a node (making it a "sink node") should
        not change the shortest paths to that node, but the path from that node to any others will have a
        distance of infinity."""
        # Select a random node to convert into a "sink node"
        sink_node = randint(0, len(graph) - 1)

        # Copy the graph and remove all outgoing edges from the selected node
        graph_with_sink_node = deepcopy(graph)
        for j in range(len(graph)):
            graph_with_sink_node[sink_node][j] = 0

        # Compute distances on the modified graph
        dist_matrix_with_sink = shortest_path(graph_with_sink_node, method=method)

        # Original distances
        dist_matrix_original = shortest_path(graph, method=method)

        # Validate that the paths to the sink node remain unchanged
        for i in range(len(graph)):
            self.assertEqual(dist_matrix_original[i][sink_node], dist_matrix_with_sink[i][sink_node])

        # Validate paths from the sink node are infinite (except to itself)
        for j in range(len(graph)):
            if j != sink_node:
                self.assertEqual(dist_matrix_with_sink[sink_node][j], np.inf)


if __name__ == "__main__":
    unittest.main()
