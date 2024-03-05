from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Given the same graph, the same source and destination vertices,
        but with one edge weight incremented by a certain amount,
        the new shortest path length should be at least the original shortest path length."""
        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Increase the weight of a single edge
        follow_graph = [row[:] for row in graph]
        follow_graph[0][1] += 1  # Increment the weight of edge (0, 1)

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_distance, original_distance)


if __name__ == "__main__":
    unittest.main()
