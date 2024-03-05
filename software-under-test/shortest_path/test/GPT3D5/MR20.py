from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test20(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 20: Given the same graph, the source and destination vertices swapped,
        the output should be the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input: swapping the source and destination vertices
        follow_out = shortest_path(graph, method=method)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
