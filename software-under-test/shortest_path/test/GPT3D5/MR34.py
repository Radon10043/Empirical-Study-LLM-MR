from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(load_test_cases)
    def test34(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 34: Given the same graph and vertices, the output of the shortest path should remain the same if
        the same graph is represented using a different mutable data structure with the exact same elements."""
        from collections import defaultdict

        # Get source output using a list representation of the graph
        source_out_list = shortest_path(graph, method=method)[src][dst]

        # Ensure each row of the graph is represented as a dictionary
        graph_dict = [{idx: val for idx, val in enumerate(row)} for row in graph]

        # Convert the graph to a different mutable data structure (defaultdict)
        # dd_graph = [defaultdict(int, enumerate(row)) for row in graph]
        dd_graph = np.array([list(row.values()) for row in graph])

        # Get follow-up output using the converted data structure
        follow_out_dd = shortest_path(dd_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out_list, follow_out_dd)


if __name__ == "__main__":
    unittest.main()
