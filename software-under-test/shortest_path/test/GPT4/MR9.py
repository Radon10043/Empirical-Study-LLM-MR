import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 9: The shortest path using predecessors matrix should match the direct computation
        of shortest paths."""
        csgraph = csr_matrix(graph)

        # Source output: direct computation of shortest paths
        source_out = shortest_path(csgraph, method=method, return_predecessors=False)

        # Follow-up output: compute shortest paths using predecessors
        _, predecessors = shortest_path(csgraph, method=method, return_predecessors=True)

        # Verification: reconstruct paths using predecessors and compare with direct computation
        num_vertices = len(predecessors)
        for src in range(num_vertices):
            for dst in range(num_vertices):
                path = get_shortest_path(predecessors, src, dst)
                path_cost = 0
                for i in range(len(path) - 1):
                    path_cost += csgraph[path[i], path[i + 1]]
                self.assertEqual(path_cost, source_out[src][dst])


if __name__ == "__main__":
    unittest.main()
