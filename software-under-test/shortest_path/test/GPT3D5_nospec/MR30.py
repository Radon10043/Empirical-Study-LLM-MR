import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 30: Given the same graph, source, and destination vertices,
        if we add a new vertex and connect it to the source and destination vertices, 
        the shortest path from source to destination should consider the effect of the new vertex."""
        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new vertex and connecting it to the source and destination vertices
        follow_graph = deepcopy(graph)
        for i in range(len(graph)):
            follow_graph[i].append(0)
        follow_graph.append([0 for _ in range(len(graph) + 1)])
        follow_graph[src][-1] = randint(1, 100)
        follow_graph[-1][dst] = randint(1, 100)

        # Get follow-up output
        modified_shortest_path = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreater(modified_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
