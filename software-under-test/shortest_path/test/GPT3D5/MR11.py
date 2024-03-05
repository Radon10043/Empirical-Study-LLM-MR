from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: Given the same graph, the same source and destination vertices,
        but with different algorithms, the output should have the property of monotonicity."""
        # Get source outputs
        source_out = shortest_path(graph, method=method)[src][dst]
        follow_out = shortest_path(graph, method="BF")[src][dst]  # Using a different algorithm

        # Verification - Monotonicity
        self.assertTrue(source_out >= follow_out)


if __name__ == "__main__":
    unittest.main()
