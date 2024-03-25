from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test37(self, img: np.array, angle: float):
        """Metamorphic Relation 37: Rotating the image and then rotating the result by 180 degrees should result in the same output as rotating the original image by 180 degrees."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.rotate(source_out, 180)  # Rotate the result by 180 degrees

        # Verification
        expected_out = ndimage.rotate(img, 180)  # Rotate the original image by 180 degrees
        self.assertTrue(np.any(follow_out - expected_out) == 0) # Fixed


if __name__ == "__main__":
    unittest.main()
