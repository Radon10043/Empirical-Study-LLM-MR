from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test12(self, img: np.array, angle: float):
        """Metamorphic Relation 12: Rotating the image by 45 degrees and then rotating the result by -45 degrees should result in the same output as the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle1 = 45  # 45 degrees
        follow_angle2 = -45  # -45 degrees

        # Get follow-up output
        temp_out = ndimage.rotate(img, follow_angle1)  # Rotate the original image by 45 degrees
        follow_out = ndimage.rotate(temp_out, follow_angle2)  # Rotate the result by -45 degrees

        # Verification
        expected_out = img  # Original image
        self.assertTrue(np.any(follow_out - expected_out) == 0) # Fixed


if __name__ == "__main__":
    unittest.main()
