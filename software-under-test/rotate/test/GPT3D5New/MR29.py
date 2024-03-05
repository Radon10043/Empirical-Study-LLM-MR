from utils import *

# fixed
class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test29(self, img: np.array, angle: float):
        """Metamorphic Relation 29: Rotating the image by -angle should result in the same output as rotating the horizontally flipped image by -angle."""
        # Get source output
        source_out = ndimage.rotate(img, -angle)

        # Construct follow-up input
        follow_input = np.fliplr(img)  # Horizontal flip of the original input

        # Get follow-up output
        follow_out = ndimage.rotate(follow_input, -angle)  # Rotate the horizontally flipped input by -angle

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)   # Fixed


if __name__ == "__main__":
    unittest.main()
