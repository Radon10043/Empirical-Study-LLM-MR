from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test36(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 36: Given the same graph, the same source and destination vertices, 
        but with an additional edge between two vertices, 
        the shortest path length should remain the same or decrease."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Add an additional edge with a lower weight
        follow_graph = [row[:] for row in graph]
        follow_graph[0][1] = 1  # Add an edge (0, 1) with weight 1

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()
