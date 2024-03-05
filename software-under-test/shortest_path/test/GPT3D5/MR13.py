from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test13(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 13: Given the same graph, the same source and destination vertices,
        but with the weights multiplied by a positive constant, the shortest path remains the same."""
        # Get source output
        _, predecessors = shortest_path(graph, method=method, return_predecessors=True)
        if predecessors[src][dst] == -9999:
            unittest.skip("No path from source to destination")
        source_out = self.get_shortest_path(predecessors, src, dst)

        follow_graph = [[weight * 2 for weight in row] for row in graph]

        # Get folllow-up output
        _, predecessors = shortest_path(follow_graph, method=method, return_predecessors=True)
        follow_out = self.get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
