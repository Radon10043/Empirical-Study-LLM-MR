import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 11: Adding a disconnected subgraph to the original graph should not affect existing shortest paths."""
        directed = choice([True, False])

        # Get source output for all pairs
        source_out = shortest_path(graph, method=method, directed=directed)

        # Add a disconnected subgraph
        extended_graph = graph.copy()
        source_v_num = len(graph)
        extended_graph.append([0] * source_v_num)
        extended_graph.append([0] * source_v_num)
        for i in range(len(extended_graph)):
            extended_graph[i].append(0)
            extended_graph[i].append(0)
        extended_graph[source_v_num][source_v_num + 1] = 1

        # Get follow-up output for the same nodes as in the original graph
        follow_out = shortest_path(extended_graph, method=method, directed=directed)

        # Verification
        # We only compare the sections of the matrices that correspond to the original graph
        self.assertTrue(np.array_equal(source_out, follow_out[:source_out.shape[0], :source_out.shape[1]]))


if __name__ == "__main__":
    unittest.main()
