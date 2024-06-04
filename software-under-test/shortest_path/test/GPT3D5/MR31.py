import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Given the same graph, the same source and destination vertices, 
        but with the graph modified to exclude specific edges, the result should remain unchanged or path may be longer."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify the graph to exclude specific edges
        follow_graph = [[0 if x < 5 else x for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out) or np.all(follow_out >= source_out))


if __name__ == "__main__":
    unittest.main()
