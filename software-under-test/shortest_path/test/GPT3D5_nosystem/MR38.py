import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Given the same graph, if the source is the same as the destination vertex,
        and the graph contains cycles, the output of the shortest path should be negative if there are negative weight cycles."""

        graph_with_cycles = create_graph_with_cycles(graph)
        shortest_path_result = shortest_path(graph_with_cycles, method=method)

        self.assertTrue(np.any(shortest_path_result[src] < 0))


if __name__ == "__main__":
    unittest.main()
