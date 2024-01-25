from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test7(self, img: np.array, angle: float):
        """Metamorphic Relation 7: Rotating the image by 90 degrees, 180 degrees, and 270 degrees successively is equivalent to rotating the image by 270 degrees once."""
        # Get source output
        output_90 = ndimage.rotate(img, 90)
        output_180 = ndimage.rotate(output_90, 90)
        output_270 = ndimage.rotate(output_180, 90)

        # Construct follow-up input
        follow_angle = 270

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.array_equal(output_270, follow_out))


if __name__ == "__main__":
    unittest.main()
