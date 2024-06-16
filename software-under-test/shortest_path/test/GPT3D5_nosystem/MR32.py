import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Given the same graph, the same source and destination vertices, and if the graph is a complete graph, 
        where every pair of distinct vertices is connected by a unique edge, the shortest path should always be either the weight of the edge between the two vertices 
        or the sum of the weights of the edges in the shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        complete_graph = create_complete_graph(graph)
        
        # Get follow-up output
        follow_out = shortest_path(complete_graph, method=method)

        # Verification
        self


if __name__ == "__main__":
    unittest.main()