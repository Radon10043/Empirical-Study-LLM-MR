import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 14: Concatenating two paths to form a longer path should not yield
        a distance shorter than the shortest path between the same start and end points."""
        # Get original distances
        original_dist_matrix = shortest_path(graph, method=method)

        # Randomly select two intermediate points
        intermediate_point1 = np.random.randint(low=0, high=len(graph))
        intermediate_point2 = np.random.randint(low=0, high=len(graph))

        # Calculate a potential composite path through both intermediates
        for src in range(len(graph)):
            for dst in range(len(graph)):
                # Composite path passing through two intermediates
                composite_distance = (original_dist_matrix[src][intermediate_point1] +
                                    original_dist_matrix[intermediate_point1][intermediate_point2] +
                                    original_dist_matrix[intermediate_point2][dst])
                # Verify this composite path is not shorter than direct shortest path
                self.assertLessEqual(original_dist_matrix[src][dst], composite_distance)


if __name__ == "__main__":
    unittest.main()
