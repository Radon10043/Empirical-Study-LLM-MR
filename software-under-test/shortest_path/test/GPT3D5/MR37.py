from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test37(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 37: Given the same graph, the same source and destination vertices,
        but with all weights incremented by 1, the resulting shortest path length should remain the same."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Increment all weights in the graph by 1
        follow_graph = [[weight + 1 for weight in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_distance, new_distance)


if __name__ == "__main__":
    unittest.main()
