import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
import scipy as sp


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: If the 'directed' flag is toggled, the shortest path distance 
        in a directed graph may either stay the same or increase if the reverse edge does not exist."""
        # Get source output assuming the graph is directed
        directed_distance = shortest_path(graph, method=method, directed=True)[src][dst]

        # Get follow-up output assuming the graph is undirected, allowing traversal in both directions
        undirected_distance = shortest_path(graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertLessEqual(undirected_distance, directed_distance)


if __name__ == "__main__":
    unittest.main()
