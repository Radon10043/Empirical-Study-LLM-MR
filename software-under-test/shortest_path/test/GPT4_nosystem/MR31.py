import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 31: Doubling the weight of an edge should not create a new shortest path
        that uses that edge if it was not part of the shortest path before the weight was doubled."""
        # Select a random edge to double its weight
        i, j = randint(0, len(graph) - 1), randint(0, len(graph) - 1)
        while i == j or graph[i][j] == 0:  # Ensure a valid non-zero edge is selected
            i, j = randint(0, len(graph) - 1), randint(0, len(graph) - 1)

        # Get original shortest paths and record if the edge is used
        _, pred = shortest_path(graph, method=method, return_predecessors=True)
        source_path = get_shortest_path(pred, src, dst)

        src_is_edge_used = True
        if i not in source_path or j not in source_path:
            src_is_edge_used = False
        else:
            src_is_edge_used = source_path.index(j) == source_path.index(i) + 1

        # Double the weight of the selected edge
        graph_with_doubled_edge = deepcopy(graph)
        graph_with_doubled_edge[i][j] *= 2

        # Get shortest paths after doubling the edge weight
        _, pred = shortest_path(graph_with_doubled_edge, method=method, return_predecessors=True)
        follow_path = get_shortest_path(pred, src, dst)

        fol_is_edge_used = True
        if i not in follow_path or j not in follow_path:
            fol_is_edge_used = False
        else:
            fol_is_edge_used = follow_path.index(j) == follow_path.index(i) + 1

        # Verify the edge is not newly used if it was not used before
        self.assertEqual(src_is_edge_used, fol_is_edge_used)


if __name__ == "__main__":
    unittest.main()
