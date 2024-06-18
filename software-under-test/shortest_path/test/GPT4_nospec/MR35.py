import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, start: int, stop: int, algo: str):
        """Metamorphic Relation 35: Permuting the nodes of the graph keeping the edges between them intact should not change the shortest path distance."""
        # Map current nodes to their new permuted indices
        permuted_indices = np.random.permutation(len(graph))
        node_map = dict(zip(range(len(graph)), permuted_indices))

        # Permuted graph
        follow_graph = permute_graph(graph, node_map)

        # Adjust src and dst according to the permutation
        permuted_start = node_map[start]
        permuted_stop = node_map[stop]

        # Get the shortest path for the original and permuted graphs
        original_distance = shortest_path(graph, src=start, dst=stop, method=algo)[start][stop]
        permuted_distance = shortest_path(follow_graph, src=permuted_start, dst=permuted_stop, method=algo)[permuted_start][permuted_stop]

        # Verify the shortest path lengths are equal for both the original and the permuted graphs
        self.assertEqual(original_distance, permuted_distance)


if __name__ == "__main__":
    unittest.main()
