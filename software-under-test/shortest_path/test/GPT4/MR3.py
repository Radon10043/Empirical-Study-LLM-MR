import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test3(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 3: Reversing a directed graph and querying the shortest path 
        from the destination to the source should provide the same result as the original graph when querying
        from the source to the destination."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)[src][dst]

        # Reverse the graph
        reversed_graph = np.transpose(graph)
        reversed_graph = np.ascontiguousarray(reversed_graph)

        # Get follow-up output
        follow_out = shortest_path(reversed_graph, method=method, directed=True)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
