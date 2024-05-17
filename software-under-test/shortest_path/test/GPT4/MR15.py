import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *

from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 15: If a node is removed from the graph, and it was not part of the shortest path 
        between any other two nodes, then the shortest path between these nodes should remain unchanged."""
        # Get source output
        source_out, predecessors = shortest_path(csr_matrix(graph), return_predecessors=True)

        # Get the shortest path between the source and destination nodes
        remove_node = 0
        path = get_shortest_path(predecessors, src, dst)
        if remove_node in path:
            self.skipTest("Node to be removed is part of the shortest path between the source and destination nodes")

        # Remove a node from the graph
        follow_graph = graph.copy()
        follow_graph.pop(remove_node)
        for row in follow_graph:
            row.pop(remove_node)

        # Get follow-up output
        follow_out = shortest_path(csr_matrix(follow_graph))

        # Verification
        self.assertAlmostEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()
