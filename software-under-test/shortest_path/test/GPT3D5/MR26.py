import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 26: Given the same graph, the same source and destination vertices,
        but with some edge weights changed to positive infinity, the result should remain unchanged or path may be longer."""
        for i in range(len(graph)):
            for j in range(len(graph)):
                if randint(1, 100) <= 50:
                    graph[i][j] *= 1000

        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify graph by changing some edge weights to positive infinity
        follow_graph = [[float('inf') if x > 100 else x for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out) or np.all(follow_out >= source_out))


if __name__ == "__main__":
    unittest.main()
