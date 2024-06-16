import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph, if a vertex is added with edges to and from all existing vertices, 
        the shortest path values between the original vertices and the new vertex should be the weight of the edge between them and the source vertex."""
        
        extended_graph = add_vertex_to_graph(graph)
        source_out = shortest_path(graph, method=method)
        extended_out = shortest_path(extended_graph, method=method)

        # Check the shortest path between source and destination nodes
        self.assertEqual(extended_out[src][-1], extended_graph[src][-1])
        self.assertEqual(extended_out[-1][dst], extended_graph[-1][dst])


if __name__ == "__main__":
    unittest.main()