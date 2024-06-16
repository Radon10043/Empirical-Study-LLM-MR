import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 36: Given the same graph, the same source and destination vertices, if the graph is a complete graph where every vertex is connected to every other vertex,
        the shortest path from a source vertex to any other vertex should be the weight of the edge between the source and destination vertices."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        follow_graph = graph.copy()
        for i in range(len(follow_graph)):
            for j in range(len(follow_graph)):
                if i != j and follow_graph[i][j] == 0:
                    follow_graph[i][j] = randint(1, 100)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(follow_out, graph))


if __name__ == "__main__":
    unittest.main()
