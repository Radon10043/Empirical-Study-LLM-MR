from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test21(self, img: np.array, angle: float):
        """Metamorphic Relation 21: Rotating the image by 90 degrees and then rotating the result by -90 degrees should result in the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle1 = 90  # 90 degrees
        follow_angle2 = -90  # -90 degrees

        # Get follow-up output
        temp_out = ndimage.rotate(img, follow_angle1)  # Rotate the original image by 90 degrees
        follow_out = ndimage.rotate(temp_out, follow_angle2)  # Rotate the result by -90 degrees

        # Verification
        self.assertTrue(np.any(follow_out - img) == 0)


if __name__ == "__main__":
    unittest.main()
