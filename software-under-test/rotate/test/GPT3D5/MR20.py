from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test20(self, img: np.array, angle: float):
        """Metamorphic Relation 20: Rotating the image by 180 degrees followed by another rotation of 90 degrees should result in the same output as rotating the original image by 270 degrees."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle1 = 180  # 180 degrees
        follow_angle2 = 90  # 90 degrees

        # Get follow-up output
        temp_out = ndimage.rotate(img, follow_angle1)  # Rotate the original image by 180 degrees
        follow_out = ndimage.rotate(temp_out, follow_angle2)  # Rotate the result by 90 degrees

        # Verification
        expected_out = ndimage.rotate(img, 270)  # Rotate the original image by 270 degrees
        self.assertTrue(np.any(follow_out - expected_out) == 0)


if __name__ == "__main__":
    unittest.main()
