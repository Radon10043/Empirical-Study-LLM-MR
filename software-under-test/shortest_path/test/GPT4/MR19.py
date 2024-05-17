import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *
from scipy.sparse import csr_matrix


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 19: The shortest path distance from source to destination and
        destination to source should be the same in an undirected graph."""
        csgraph = csr_matrix(graph)

        # Get source to destination path length
        source_to_dest = shortest_path(csgraph, directed=False, indices=[src])[0][dst]

        # Get destination to source path length
        dest_to_source = shortest_path(csgraph, directed=False, indices=[dst])[0][src]

        # The two distances should be the same in an undirected graph
        self.assertEqual(source_to_dest, dest_to_source)


if __name__ == "__main__":
    unittest.main()
