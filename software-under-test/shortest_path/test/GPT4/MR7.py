import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 7: Reversing the direction of edges in a directed graph should not affect the
        shortest path in the original graph if the destination is set as the new source."""
        csgraph = csr_matrix(graph)

        # Assume the graph is directed and we can reverse it
        reversed_csgraph = csgraph.T

        # Source output: every node to the destination
        source_out_all_to_dst = shortest_path(csgraph)[:, dst]

        # Follow-up output: new source is the old destination
        follow_out_src_to_all = shortest_path(reversed_csgraph, indices=[dst])[0]

        # Verification for each node as a new source
        num_vertices = len(follow_out_src_to_all)
        for i in range(num_vertices):
            self.assertEqual(source_out_all_to_dst[i], follow_out_src_to_all[i])


if __name__ == "__main__":
    unittest.main()
