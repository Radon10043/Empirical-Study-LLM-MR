from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test6(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 6: Given the same graph, the source and destination vertices swapped,
        the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input
        follow_out = shortest_path(graph, method=method)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
