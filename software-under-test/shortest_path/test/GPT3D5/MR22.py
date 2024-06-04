import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Given the same graph, the same source and destination vertices,
        but with the graph modified to have a self loop added to the source vertex, the result should remain unchanged or path may be shorter."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify the graph to add a self loop to the source vertex
        follow_graph = graph.copy()
        follow_graph[src][src] = 1

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out) or np.all(follow_out <= source_out))


if __name__ == "__main__":
    unittest.main()
