import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 5: Adding a limit to Dijkstra's algorithm should not change the shortest path
        distances for paths shorter than the limit."""
        limit = np.random.randint(1, 1000)

        # Get source output without limit
        source_out = shortest_path(graph, method=method)

        # Get follow-up output with a specified limit
        follow_out = shortest_path(graph, method=method, limit=limit)

        # Verification
        num_vertices = len(source_out)
        for i in range(num_vertices):
            for j in range(num_vertices):
                if source_out[i][j] <= limit:
                    self.assertEqual(source_out[i][j], follow_out[i][j])
                else:
                    self.assertTrue(follow_out[i][j] > limit or follow_out[i][j] == np.inf)


if __name__ == "__main__":
    unittest.main()
