import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 5: Given the same graph, the same source and destination vertices,
        but with the source and destination vertices swapped, the output should be the reverse of the original output."""
        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Get follow-up output
        _, predecessors = shortest_path(graph, method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, dst, src)

        # Verification
        self.assertEqual(source_out, list(reversed(follow_out)))


if __name__ == "__main__":
    unittest.main()
