import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str):
        """ Metamorphic Relation 21: Given the same graph, the same source and destination vertices,
        if the graph is symmetric, the result should be the same regardless of whether the graph is 
        treated as directed or undirected."""
        # Make sure the graph is symmetric
        graph = np.maximum(graph, np.transpose(graph))

        # Get source output with directed=True
        source_out_directed = shortest_path(graph, method=method, directed=True)

        # Get source output with directed=False
        source_out_undirected = shortest_path(graph, method=method, directed=False)

        # Verification
        np.testing.assert_almost_equal(source_out_directed, source_out_undirected)


if __name__ == "__main__":
    unittest.main()
