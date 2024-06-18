import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: For any node 'n', the shortest path from 'src' to 'dst' passing
        through 'n' should be longer or equal to the direct shortest path from 'src' to 'dst'."""
        if src == dst:
            self.skipTest("Source and destination are the same, relation not applicable.")

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        for n in range(len(graph)):
            if n != src and n != dst:
                # Get follow-up output - first half (src to n)
                first_half = shortest_path(graph, method=method)[src][n]

                # Get follow-up output - second half (n to dst)
                second_half = shortest_path(graph, method=method)[n][dst]

                # Total distance passing through 'n'
                via_n_out = first_half + second_half

                # Verification
                self.assertGreaterEqual(via_n_out, source_out)


if __name__ == "__main__":
    unittest.main()
