import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 10: Given the same graph and the same source and destination vertices, 
        if all edge weights are multiplied by a constant, the shortest path lengths should be scaled by the same constant."""
        # Get source output
        source_out = shortest_path(graph, method=method)
    
        # Get follow-up graph with all edge weights scaled
        scaled_graph = [[x*2 for x in row] for row in graph]
    
        # Get follow-up output
        follow_out = shortest_path(scaled_graph, method=method)
    
        # Verification
        self.assertTrue(np.all(source_out*2 == follow_out))


if __name__ == "__main__":
    unittest.main()
