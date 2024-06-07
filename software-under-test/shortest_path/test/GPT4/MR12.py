import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: If we add the same constant weight to all edges in a directed acyclic graph,
        the shortest path between any two vertices might increase by at most that constant."""
        constant_weight = 5

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Increase the weight of all edges by constant_weight
        updated_graph = graph + (graph != 0).astype(int) * constant_weight

        # Get follow-up output
        follow_out = shortest_path(updated_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out <= source_out + constant_weight)


if __name__ == "__main__":
    unittest.main()
