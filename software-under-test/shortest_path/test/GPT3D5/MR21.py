from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test21(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 21: Given the same graph and vertices, the output should be the same irrespective of the path reconstruction option."""
        # Fixed
        # Get source output
        source_out = shortest_path(graph, method=method, return_predecessors=True)[0][src][dst]

        # Construct follow-up input: without path reconstruction
        follow_out = shortest_path(graph, method=method, return_predecessors=False)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
