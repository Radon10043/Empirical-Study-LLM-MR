import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 26: Given the same graph, source, and destination vertices,
        if we remove specific vertex and its associated edges, 
        the shortest path from source to destination should also not include the removed vertex."""
        if src == len(graph) - 1 or dst == len(graph) - 1:
            self.skipTest("Source or destination vertex is the removed vertex")

        # Get source output
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by removing a specific vertex and its associated edges
        def remove_specific_vertex(graph: list) -> list:
            follow_graph = deepcopy(graph)
            follow_graph.pop(len(graph) - 1)
            for i in range(len(follow_graph)):
                follow_graph[i].pop(len(graph) - 1)
            return follow_graph
        follow_graph = remove_specific_vertex(graph)

        # Get follow-up output
        _, predecessors = shortest_path(follow_graph, method=method, return_predecessors=True)
        follow_path = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertTrue(len(graph) - 1 not in follow_path)


if __name__ == "__main__":
    unittest.main()
