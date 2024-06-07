import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 31: If all edge weights are set to 1 in a weighted graph, the shortest 
        path computation should yield the same result as setting the 'unweighted' flag to True."""
        graph = csr_matrix(graph)

        # Compute shortest path with original weights
        weighted_distance = shortest_path(graph, method=method, unweighted=False)[src][dst]

        # Set all non-zero weights to 1 to simulate an unweighted graph
        unweighted_graph = graph.copy()
        unweighted_graph[unweighted_graph.nonzero()] = 1

        # Compute shortest path in the transformed graph
        unweighted_distance = shortest_path(unweighted_graph, method=method, unweighted=True)[src][dst]

        # Verification
        self.assertEqual(weighted_distance, unweighted_distance)


if __name__ == "__main__":
    unittest.main()
