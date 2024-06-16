import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str):
        """ Metamorphic Relation 16: Given the same graph, if a node is removed from the graph,
        the path length from any node to the removed node should be infinity """
        # Get source output
        source_out = shortest_path(graph, method=method)
        
        # Create a modified graph by removing a node
        modified_graph = remove_node_from_graph(graph)
        
        # Verify that the distance to the removed node is always infinity
        for i in range(len(graph)):
            self.assertEqual(source_out[i][len(graph)], np.inf)


if __name__ == "__main__":
    unittest.main()
