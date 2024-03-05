from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test10(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 10: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should still satisfy the triangle inequality."""
        # Get source outputs
        source_out = shortest_path(graph, method=method)[src][dst]
        follow_out = shortest_path(graph, method="D")[src][dst]  # Using a different algorithm

        # Verification - Triangle Inequality
        self.assertTrue(source_out <= follow_out)


if __name__ == "__main__":
    unittest.main()
