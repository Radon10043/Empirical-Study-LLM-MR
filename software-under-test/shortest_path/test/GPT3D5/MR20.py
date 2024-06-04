import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test20(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 20: Given the same graph, the same source and destination vertices,
        but only a subset of vertices and related edges are selected to form a new sub-graph, the result should remain unchanged.
        """
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Only a subset of vertices and related edges are selected to form a new sub-graph
        subgraph_vertices = [0, 2, 4]
        subgraph = [graph[i] for i in subgraph_vertices]
        subgraph = [row[i] for row in subgraph for i in subgraph_vertices]

        # Get follow-up output
        follow_out = shortest_path(subgraph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
