from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Given the same graph and vertices, removing all edges incident on a particular vertex should not affect the shortest path for other vertices."""
        import copy

        # Get source output for destination vertex
        source_out_dst = shortest_path(graph, method=method)[src][dst]

        # Remove all edges incident on destination vertex
        modified_graph = copy.deepcopy(graph)
        for i in range(len(modified_graph)):
            modified_graph[i][dst] = 0

        # Get follow-up output for destination vertex
        follow_out_dst = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_dst, follow_out_dst)

        # Get source output for a different vertex
        other_vertex = (dst + 1) % len(graph)  # Selecting a different vertex
        source_out_other = shortest_path(graph, method=method)[src][other_vertex]

        # Get follow-up output for the different vertex
        follow_out_other = shortest_path(modified_graph, method=method)[src][other_vertex]

        # Verification
        self.assertEqual(source_out_other, follow_out_other)


if __name__ == "__main__":
    unittest.main()
