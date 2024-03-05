from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph, the same source and destination vertices, and the same algorithm,
        but with all weights set to the same value, the resulting shortest path should remain the same."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Set all weights in the graph to the same value
        follow_graph = [[5 for _ in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_distance, new_distance)


if __name__ == "__main__":
    unittest.main()
