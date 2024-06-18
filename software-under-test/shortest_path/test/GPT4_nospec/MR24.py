import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 24: For any intermediate node, the shortest path from the source
        to that intermediate node, plus the shortest path from that node to the destination,
        should be greater than or equal to the shortest path from the source to the destination."""
        # Get the shortest path from src to dst
        shortest_path_src_to_dst = shortest_path(graph, method=method)[src][dst]

        for intermediate_node in range(len(graph)):
            if intermediate_node != src and intermediate_node != dst:
                # Shortest paths involving the intermediate_node
                path_src_to_intermediate = shortest_path(graph, method=method)[src][intermediate_node]
                path_intermediate_to_dst = shortest_path(graph, method=method)[intermediate_node][dst]

                # Verify that the combination of the two paths is not shorter than the direct path
                self.assertGreaterEqual(path_src_to_intermediate + path_intermediate_to_dst, shortest_path_src_to_dst)


if __name__ == "__main__":
    unittest.main()
