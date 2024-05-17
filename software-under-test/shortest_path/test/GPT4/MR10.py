import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 10: Adding or modifying an edge that does not affect the shortest path between
        a source and a destination should not change the shortest path distance."""
        csgraph = csr_matrix(graph)

        # Get source output
        source_out, predecessors = shortest_path(csgraph, method=method, return_predecessors=True)

        # Modifying csgraph
        new_csgraph = csgraph.copy()
        u, v = np.nonzero(new_csgraph)
        non_affecting_edge = (u[0], v[0])
        new_weight = new_csgraph[non_affecting_edge] + 1000  # Choose a large non-affecting weight increment
        new_csgraph[non_affecting_edge] = new_weight

        # Make sure the edge does not affect the shortest path
        path = get_shortest_path(predecessors, src, dst)
        for i in range(len(path) - 1):
            if path[i] == non_affecting_edge[0] and path[i + 1] == non_affecting_edge[1]:
                self.skipTest("The edge is affecting the shortest path")

        # Get follow-up output
        follow_out = shortest_path(new_csgraph, method=method)

        # Verification for each pair of nodes
        num_vertices = len(follow_out)
        for i in range(num_vertices):
            for j in range(num_vertices):
                if i == non_affecting_edge[0] and j == non_affecting_edge[1]:
                    continue  # Skip the modified edge
                self.assertEqual(source_out[i][j], follow_out[i][j])


if __name__ == "__main__":
    unittest.main()
