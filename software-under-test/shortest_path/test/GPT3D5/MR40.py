from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test40(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 40: Given the same graph, the same source and destination vertices,
        but with one additional edge, the shortest path should remain the same or be shorter."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Add an additional edge
        follow_graph = [row[:] for row in graph]
        follow_graph[3][4] = 3  # Add an edge (3, 4) with weight 3

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()
