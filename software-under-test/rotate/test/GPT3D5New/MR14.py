from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test14(self, img: np.array, angle: float):
        """Metamorphic Relation 14: Rotating an image and its vertically flipped counterpart by the same angle should yield vertically flipped outputs."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_input = np.flipud(img)  # Vertical flip of the original input

        # Get follow-up output
        follow_out = ndimage.rotate(follow_input, angle)

        # Verification
        self.assertTrue(np.all(np.flipud(follow_out) - source_out) == 0)



if __name__ == "__main__":
    unittest.main()
