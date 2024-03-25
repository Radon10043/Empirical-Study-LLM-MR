from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test15(self, img: np.array, angle: float):
        """Metamorphic Relation 15: Flipping the image horizontally and then rotating the result by 180 degrees should result in the same output as flipping the original image vertically."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_input = np.fliplr(img)  # Horizontal flip of the original input

        # Get follow-up output
        follow_out = ndimage.rotate(follow_input, 180)  # Rotate the horizontally flipped input by 180 degrees

        # Verification
        expected_out = np.flipud(img)  # Vertical flip of the original input
        self.assertTrue(np.any(follow_out - expected_out) == 0) # Fixed


if __name__ == "__main__":
    unittest.main()
