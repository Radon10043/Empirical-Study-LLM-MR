import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test42(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 42: Shuffling the rows and corresponding columns of the graph (relabeling nodes) should not change the distance of the shortest path."""
        # Shuffle the graph rows and corresponding columns
        shuffled_indices = np.random.permutation(len(graph))
        shuffled_graph = graph[shuffled_indices, :][:, shuffled_indices]

        # Map original src and dst to shuffled indices
        shuffled_src = np.where(shuffled_indices == src)[0][0]
        shuffled_dst = np.where(shuffled_indices == dst)[0][0]

        # Calculate the shortest path on both the original and the shuffled graphs
        original_distance = shortest_path(graph, src=src, dst=dst, method=method)[src][dst]
        shuffled_distance = shortest_path(shuffled_graph, src=shuffled_src, dst=shuffled_dst, method=method)[shuffled_src][shuffled_dst]

        # Verify that the distance of the shortest path remains the same after shuffling (relabeling) the nodes
        self.assertEqual(original_distance, shuffled_distance)

if __name__ == "__main__":
    unittest.main()
