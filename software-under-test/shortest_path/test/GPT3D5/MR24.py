from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test24(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 24: Given the same graph and vertices, but with the edge weights scaled by a constant factor, the output should also be scaled by the same factor."""
        scale_factor = 2
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with scaled edge weights
        follow_graph = [[weight * scale_factor for weight in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertAlmostEqual(source_out * scale_factor, follow_out)


if __name__ == "__main__":
    unittest.main()
