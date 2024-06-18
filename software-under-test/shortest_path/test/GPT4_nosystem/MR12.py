import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 12: The shortest path between any two nodes should not become
        longer when considering a subgraph that only contains a subset of nodes which includes
        these two nodes."""
        if src == len(graph) - 1 or dst == len(graph) - 1:
            self.skipTest("SKIP.")

        # Create a subgraph containing only the subset of nodes
        subgraph = deepcopy(graph)
        for i in range(len(subgraph)):
            subgraph[i].pop(-1)
        subgraph.pop(-1)

        # Get full distance matrix
        full_dist_matrix = shortest_path(graph)

        # Create a subgraph containing only the subset of nodes
        subgraph = deepcopy(graph)
        for i in range(len(subgraph)):
            subgraph[i].pop(-1)
        subgraph.pop(-1)

        # Compute the shortest paths for the subgraph
        subgraph_dist_matrix = shortest_path(subgraph, method=method)
        
        # Compare distances in subgraph to those in the full graph
        for i in range(len(subgraph)):
            for j in range(len(subgraph)):
                self.assertLessEqual(subgraph_dist_matrix[i][j], full_dist_matrix[i][j])


if __name__ == "__main__":
    unittest.main()
