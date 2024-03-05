from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test15(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 15: Given the same graph, the same source and destination vertices,
        but with the weights changed with a constant offset, the shortest path remains the same."""
        # Get source output
        _, source_predecessors = shortest_path(graph, method=method, return_predecessors=True)
        source_out = get_shortest_path(source_predecessors, src, dst)

        offset = 5
        follow_graph = [[weight + offset for weight in row] for row in graph]

        # Get follow-up output
        _, predecessors = shortest_path(follow_graph, method=method, return_predecessors=True)
        follow_out = get_shortest_path(predecessors, src, dst)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
