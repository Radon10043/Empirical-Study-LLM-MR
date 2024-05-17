import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1))
    def test9(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 9: The shortest path using predecessors matrix should match the direct computation
        of shortest paths."""
        csgraph = csr_matrix(graph)

        # Source output: direct computation of shortest paths
        source_out, _ = shortest_path(csgraph, method=method, return_predecessors=False)

        # Follow-up output: compute shortest paths using predecessors
        _, predecessors = shortest_path(csgraph, method=method, return_predecessors=True)

        # Verification: reconstruct paths using predecessors and compare with direct computation
        num_vertices = len(predecessors)
        for src in range(num_vertices):
            for dst in range(num_vertices):
                path_cost = 0
                current = dst
                while predecessors[src][current] != -9999:  # Assuming -9999 is the marker of no predecessor
                    path_cost += csgraph[predecessors[src][current], current]
                    current = predecessors[src][current]
                self.assertEqual(path_cost, source_out[src][dst])


if __name__ == "__main__":
    unittest.main()
