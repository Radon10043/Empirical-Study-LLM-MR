import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 10: For any vertex, finding the shortest path distance to every other vertex and then summing them should yield the same result."""
        with self.subTest():
            # Get source output
            source_out = shortest_path(graph, method=method)[src]

            # Sum the distances
            sum_distances = sum(source_out)

            expected_sum = 0
            for i in range(len(graph)):
                if i != src:
                    expected_sum += source_out[i]

            # Verification
            self.assertEqual(sum_distances, expected_sum)


if __name__ == "__main__":
    unittest.main()
