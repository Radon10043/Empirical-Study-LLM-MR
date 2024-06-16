import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: Given the same graph and the same source and destination vertices, 
        if the graph is directed, and then converted to an undirected graph, the results should be the same."""
        # Get source output with directed=True
        source_out_directed = shortest_path(graph, method=method, directed=True)

        # Get source output with directed=False
        source_out_undirected = shortest_path(graph, method=method, directed=False)

        # Verification
        self.assertTrue(np.all(source_out_directed == source_out_undirected))


if __name__ == "__main__":
    unittest.main()