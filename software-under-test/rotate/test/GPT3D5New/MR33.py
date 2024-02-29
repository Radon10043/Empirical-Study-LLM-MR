from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test33(self, img: np.array, angle: float):
        """Metamorphic Relation 33: Rotating the image using different order parameters will guarantee consistency if the order parameters are swapped."""
        # Get source output with the original order
        source_out = ndimage.rotate(img, angle, order=3)

        # Construct follow-up input with swapped order parameters
        follow_out = ndimage.rotate(img, angle, order=0)  # Use a different order parameter

        # Verification
        self.assertTrue(np.all(follow_out - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
