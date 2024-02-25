from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test36(self, img: np.array, angle: float):
        """Metamorphic Relation 36: Rotating an image and then rotating the result by 90 degrees and 90 degrees should result in the same output as rotating the original image by 180 degrees."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle1 = 90  # 90 degrees
        follow_angle2 = 90  # 90 degrees

        # Get follow-up output
        temp_out = ndimage.rotate(img, angle)  # Rotate the original image
        follow_out = ndimage.rotate(temp_out, follow_angle1)  # Rotate the result by 90 degrees
        follow_out = ndimage.rotate(follow_out, follow_angle2)  # Rotate the result by another 90 degrees

        # Verification
        expected_out = ndimage.rotate(img, 180)  # Rotate the original image by 180 degrees
        self.assertTrue(np.all(follow_out - expected_out) == 0)


if __name__ == "__main__":
    unittest.main()
