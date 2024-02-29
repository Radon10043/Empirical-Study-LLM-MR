from utils import *

#fixed
class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test23(self, img: np.array, angle: float):
        """Metamorphic Relation 23: Rotating the image by -angle should result in the same output as rotating the vertically flipped image by angle."""
        # Get source output
        source_out = ndimage.rotate(img, -angle)

        # Construct follow-up input
        follow_input = np.flipud(img)  # Vertical flip of the original input

        # Get follow-up output
        follow_out = ndimage.rotate(follow_input, angle)  # Rotate the vertically flipped input by -angle

        # Verification
        self.assertTrue(np.all(follow_out - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
