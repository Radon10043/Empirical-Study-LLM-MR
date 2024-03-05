from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Given the same graph, the same source and destination vertices,
        but with the graph represented as a completely disconnected graph, 
        the shortest path length should be infinity."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Create a disconnected graph
        follow_graph = [[float('inf') if weight!=0 else 0 for weight in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(new_distance, float('inf'))


if __name__ == "__main__":
    unittest.main()
