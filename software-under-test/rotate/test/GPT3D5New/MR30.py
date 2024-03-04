from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test30(self, img: np.array, angle: float):
        """Metamorphic Relation 30: Rotating the image by 180 degrees and then rotating the result by -90 degrees should result in the same output as rotating the original image by 90 degrees."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle1 = 180  # 180 degrees
        follow_angle2 = -90  # -90 degrees

        # Get follow-up output
        temp_out = ndimage.rotate(img, follow_angle1)  # Rotate the original image by 180 degrees
        follow_out = ndimage.rotate(temp_out, follow_angle2)  # Rotate the result by -90 degrees

        # Verification
        expected_out = ndimage.rotate(img, 90)  # Rotate the original image by 90 degrees
        self.assertTrue(np.all(follow_out - expected_out) == 0)


if __name__ == "__main__":
    unittest.main()