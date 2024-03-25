from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test27(self, img: np.array, angle: float):
        """Metamorphic Relation 27: Rotating the image by 180 degrees and then rotating the result by -180 degrees should result in the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input 
        follow_angle1 = 180  # 180 degrees
        follow_angle2 = -180  # -180 degrees

        # Get follow-up output
        temp_out = ndimage.rotate(img, follow_angle1)  # Rotate the original image by 180 degrees
        follow_out = ndimage.rotate(temp_out, follow_angle2)  # Rotate the result by -180 degrees

        # Verification
        self.assertTrue(np.all(follow_out - img) == 0)  # Fixed


if __name__ == "__main__":
    unittest.main()
