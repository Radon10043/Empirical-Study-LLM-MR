from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test32(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 32: Given the same graph, the same source and destination vertices,
        but with edge weights multiplied by a constant factor,
        the new shortest path length should be multiplied by the same factor."""
        scale_factor = 2

        # Get the original shortest path length
        original_distance = shortest_path(graph, method=method)[src][dst]

        # Multiply all edge weights by the scale factor
        follow_graph = [[weight * scale_factor for weight in row] for row in graph]

        # Get the new shortest path length
        new_distance = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertAlmostEqual(new_distance, original_distance * scale_factor)


if __name__ == "__main__":
    unittest.main()
