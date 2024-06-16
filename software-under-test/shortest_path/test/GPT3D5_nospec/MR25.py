import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 25: Given the same graph, source, and destination vertices,
        if we add a new vertex with edges connecting it to the existing vertices,
        the shortest path from source to destination should not be shorter than the original shortest path."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new vertex with edges connecting it to the existing vertices
        follow_graph = deepcopy(graph)
        for i in range(len(graph)):
            follow_graph[i].append(randint(1, 100))
        follow_graph.append([randint(1, 100) for _ in range(len(graph) + 1)])

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
