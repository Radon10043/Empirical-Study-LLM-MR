import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test4(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 4: Removing an vertex not in the shortest path should not
        affect the shortest path distance."""
        # Get source output
        matrix, predcessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = matrix[src][dst]

        # Construct follow-up input by removing a vertex not in the shortest path
        path_nodes = set(get_shortest_path(predcessors, src, dst))

        vertex_to_remove = len(graph) - 1
        if vertex_to_remove in path_nodes:
            self.skipTest("Vertex to remove is in the shortest path")
        follow_graph = deepcopy(graph)
        follow_graph.pop(vertex_to_remove)
        for i in range(len(follow_graph)):
            follow_graph[i].pop(vertex_to_remove)


        # Adjust src and dst if necessary
        follow_src = src if src < vertex_to_remove else src - 1
        follow_dst = dst if dst < vertex_to_remove else dst - 1

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[follow_src][follow_dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
