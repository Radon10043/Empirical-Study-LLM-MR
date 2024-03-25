from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test13(self, img: np.array, angle: float):
        """Metamorphic Relation 13: Rotating the image by a positive angle and then rotating the result by a negative angle should result in the same output as rotating the original image by the absolute difference between the two angles."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle1 = angle + 30  # Positive angle
        follow_angle2 = -30  # Negative angle

        # Get follow-up output
        temp_out = ndimage.rotate(img, follow_angle1)  # Rotate the original image by a positive angle
        follow_out = ndimage.rotate(temp_out, follow_angle2)  # Rotate the result by a negative angle

        # Verification
        expected_out = ndimage.rotate(img, abs(follow_angle1 - follow_angle2))  # Rotate the original image by the absolute difference between the two angles
        self.assertTrue(np.any(follow_out - expected_out) == 0) # Fixed


if __name__ == "__main__":
    unittest.main()
