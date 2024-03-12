import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(gen_tcs_randomly(1000))
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: Given the same graph, the source and destination vertices swapped,
        the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
