import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: Given the same graph, the same source and destination vertices,
        but with the source and destination vertices shifted by a constant, the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        shifted_src = (src + 2) % len(graph)  # shifting source vertex by 2
        shifted_dst = (dst + 2) % len(graph)  # shifting destination vertex by 2

        # Get follow-up output
        follow_out = shortest_path(graph, method)[shifted_src][shifted_dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
