import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test40(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 40: Changing the algorithm ('method' parameter) should not affect the 
        computed distances between nodes in the graph, assuming all algorithms are correct."""
        graph = csr_matrix(graph)

        # Get source output using original algorithm
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Test with each alternative algorithm and compare the result with the original distance
        for alternative_method in ['FW', 'D', 'BF', 'auto']:
            if method != alternative_method:
                follow_distance = shortest_path(graph, method=alternative_method)[src][dst]
                self.assertEqual(original_distance, follow_distance)


if __name__ == "__main__":
    unittest.main()
