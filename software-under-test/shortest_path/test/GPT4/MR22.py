import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test1(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Removing a vertex with the maximum number of edges (a hub) and edges associated
        with it may alter shortest paths, but only for paths that had passed through that hub."""
        csgraph = csr_matrix(graph)

        # Find the vertex with the maximum number of edges (hub)
        hub_vertex = csgraph.sum(axis=0).argmax()

        # Get the original shortest paths
        original_path_lengths, original_predecessors = shortest_path(csgraph, return_predecessors=True)

        # Remove the hub vertex
        mask = np.ones(csgraph.shape[0], dtype=bool)
        mask[hub_vertex] = False
        reduced_csgraph = csgraph[mask][:, mask]

        # Get the shortest paths without the hub vertex
        reduced_path_lengths, reduced_predecessors = shortest_path(reduced_csgraph, return_predecessors=True)

        # Verification: Check paths between the vertices that do not pass through the hub
        num_vertices = csgraph.shape[0]
        for i in range(num_vertices):
            if i == hub_vertex:
                continue
            for j in range(num_vertices):
                if j == hub_vertex:
                    continue
                original_path = []
                k = j
                while original_predecessors[i, k] != -1 and k != i:
                    original_path.append(k)
                    k = original_predecessors[i, k]
                original_path.append(i)
                original_path.reverse()

                # If the original path did not include the hub_vertex, the path should remain the same
                if hub_vertex not in original_path:
                    i_reduced = i if i < hub_vertex else i - 1
                    j_reduced = j if j < hub_vertex else j - 1
                    self.assertEqual(original_path_lengths[i, j], reduced_path_lengths[i_reduced, j_reduced])


if __name__ == "__main__":
    unittest.main()
