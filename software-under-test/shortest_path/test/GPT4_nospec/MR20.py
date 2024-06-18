import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 20: If graph G' is a supergraph of G (contains G plus additional edges and/or vertices),
        then the shortest path in G' from src to dst should be shorter or equal to the shortest path in G."""
        # Get shortest path cost in original graph G
        source_out = shortest_path(graph, method=method)[src][dst]

        # Create a supergraph G', which includes G plus additional nodes and edges
        supergraph = deepcopy(graph)
        for row in supergraph:
            row.append(randint(0, 100))
        supergraph.append([randint(0, 100) for _ in range(len(supergraph[0]))])

        # Get shortest path cost in supergraph G'
        follow_out = shortest_path(supergraph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
