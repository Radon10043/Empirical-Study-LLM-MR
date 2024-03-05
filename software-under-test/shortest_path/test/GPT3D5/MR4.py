from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test4(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 4: Given the same graph, the same source and destination vertices,
        but representing a sub-graph (specific indices), the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, indices=None)[src][dst]

        # Construct follow-up input
        indices = [1, 3, 5]  # Example indices
        follow_out = shortest_path(graph, method=method, indices=indices)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
