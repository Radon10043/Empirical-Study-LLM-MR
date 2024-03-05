from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test2(self, img: np.array, angle: float):   # Fixed
        """Metamorphic Relation 2: Rotating the image by angle and -angle will result in the same output except for a change in axes."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = -angle

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.any(source_out - follow_out) == 0)


if __name__ == "__main__":
    unittest.main()