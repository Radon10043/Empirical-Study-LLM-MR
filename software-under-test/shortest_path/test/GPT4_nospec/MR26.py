import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 26: For any node u directly connected to src (src-u edge), 
        the shortest path from u to dst should be less than or equal to the shortest path from src to dst minus the edge weight src-u."""
        # Get the current shortest path weight from src to dst
        shortest_path_cost = shortest_path(graph, method=method)[src][dst]

        for u in range(len(graph)):
            # If there's a direct connection from src to u
            if graph[src][u] not in (0, float('inf')):
                # Get the shortest path weight from u to dst
                shortest_path_cost_u_to_dst = shortest_path(graph, method=method)[u][dst]
                src_to_u_edge_weight = graph[src][u]

                # The shortest path from u to dst should be less than or equal to shortest_path_cost - src_to_u_edge_weight
                self.assertLessEqual(shortest_path_cost_u_to_dst, shortest_path_cost - src_to_u_edge_weight)


if __name__ == "__main__":
    unittest.main()
