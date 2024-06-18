import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 23: If the shortest path from src to dst passes through a node u, then for any 
        destination v, the shortest path from src to v that passes through u should be at least as long as the 
        path from src to u."""
        # Get the shortest path from src to u
        shortest_path_to_u = shortest_path(graph, src=src, dst=u, method=method)[src][u]

        # Verify for all destinations v in the graph
        for v in range(len(graph)):
            if v != src:
                # Get the shortest path from src to v via u
                distance_src_to_u = shortest_path(graph, src=src, dst=u, method=method)[src][u]
                distance_u_to_v = shortest_path(graph, src=u, dst=v, method=method)[u][v]
                total_distance_via_u = distance_src_to_u + distance_u_to_v

                # Direct distance from src to v
                direct_distance_src_to_v = shortest_path(graph, src=src, dst=v, method=method)[src][v]

                # The shortest path via u should be at least as long as the direct shortest path
                self.assertGreaterEqual(total_distance_via_u, direct_distance_src_to_v)

if __name__ == "__main__":
    unittest.main()
