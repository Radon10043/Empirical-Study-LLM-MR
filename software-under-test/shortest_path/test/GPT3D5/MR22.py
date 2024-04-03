import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should follow the same sequence of vertices for the shortest path."""
        # Get source output
        predecessors = shortest_path(graph, method=method, return_predecessors=True)[1]
        source_out = get_shortest_path(predecessors, src, dst)

        # Construct follow-up input: using a different algorithm
        if method != "D":
            method = "D"
        else:
            method = "FW"
        predecessors = shortest_path(graph, method=method, return_predecessors=True)[1]
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertTrue(source_out == follow_out)


if __name__ == "__main__":
    unittest.main()
