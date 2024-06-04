import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 34: Given the same graph, the same source and destination vertices,
        but changing the source vertex, the result should change correspondingly."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Change source vertex
        if src != 1:
            new_src = 1
        else:
            src = 0

        # Get follow-up output
        follow_out = shortest_path(graph, method=method)[new_src][dst]

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
