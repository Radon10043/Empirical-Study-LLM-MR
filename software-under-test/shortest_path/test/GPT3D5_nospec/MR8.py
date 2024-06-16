import scipy
import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test8(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 8: Given the same graph, source vertex, and destination vertex, 
        swapping the source and destination vertices should produce the same shortest path."""
        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(predecessors, src, dst)

        # Get follow-up output with swapped source and destination vertices
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, dst, src)

        # Verification
        self.assertEqual(source_out, follow_out)

if __name__ == "__main__":
    unittest.main()
