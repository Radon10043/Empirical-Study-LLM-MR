import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Converting an undirected graph to a directed one by replacing 
        each undirected edge with two directed edges (one in each direction) should not change 
        the shortest path distances."""
        # Make sure the input graph is undirected for this test case
        for i in range(len(graph)):
            for j in range(i + 1, len(graph)):
                graph[i][j] = 0

        # Get source output for the undirected graph
        undirected_distance = shortest_path(graph, method=method, directed=False)[src][dst]

        # Convert undirected graph to directed by creating two directed edges for each undirected edge
        for i in range(len(graph)):
            for j in range(i + 1, len(graph)):
                graph[j][i] = graph[i][j]

        # Get follow-up output after converting to directed
        directed_distance = shortest_path(graph, method=method, directed=True)[src][dst]

        # Verification
        self.assertEqual(undirected_distance, directed_distance)


if __name__ == "__main__":
    unittest.main()
