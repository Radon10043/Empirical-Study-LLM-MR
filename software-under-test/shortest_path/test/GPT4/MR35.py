import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test35(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 35: Computing the shortest paths between a subset of nodes should yield 
        the same results as computing the shortest paths for the whole graph and extracting the relevant 
        subset."""
        indices = [src, dst]
        graph = csr_matrix(graph)

        # Compute the shortest path for the full graph
        full_distances = shortest_path(graph, method=method, directed=True)

        # Choose random subset of nodes, including src and dst
        subset = [src, dst] if indices is None else indices
        if len(subset) < graph.shape[0]:
            other_nodes = list(set(range(graph.shape[0])) - set(subset))
            subset.extend(choices(other_nodes, k=min(3, len(other_nodes))))

        # Compute the shortest paths for the nodes subset
        subset_distances = shortest_path(graph, method=method, directed=True, indices=subset)

        # Verify distances in the subset match the corresponding distances in the full set
        for i, full_src in enumerate(subset):
            for j, full_dst in enumerate(subset):
                if full_src != full_dst:
                    self.assertEqual(full_distances[full_src][full_dst], subset_distances[i][j])


if __name__ == "__main__":
    unittest.main()
