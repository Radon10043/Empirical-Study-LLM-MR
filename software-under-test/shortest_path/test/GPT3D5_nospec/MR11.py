import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: Given the same graph, source and destination vertices, 
        if the source vertex index and destination vertex index are multiplied by a positive constant k, 
        the shortest path should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with multiplied source and destination vertex indices
        follow_src = src * 3
        follow_dst = dst * 3
        follow_out = shortest_path(graph, method=method)[follow_src][follow_dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
