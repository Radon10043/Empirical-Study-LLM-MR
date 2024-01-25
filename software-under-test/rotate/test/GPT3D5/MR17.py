from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test17(self, img: np.array, angle: float):
        """Metamorphic Relation 17: Rotating the image by 360 degrees multiple times results in the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = 360  # or any other multiple of 360

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        self.assertTrue(np.array_equal(follow_out, img))


if __name__ == "__main__":
    unittest.main()
