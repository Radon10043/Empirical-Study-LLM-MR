from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test36(self, img: np.array, angle: float):
        """Metamorphic Relation 36: Rotating the image by angle A and then applying a minimum filter to the resulting image is equivalent to applying the minimum filter to the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.minimum_filter(source_out, size=3)

        # Verification
        minimum_source_out = ndimage.minimum_filter(img, size=3)
        rotated_minimum_out = ndimage.rotate(minimum_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_minimum_out))


if __name__ == "__main__":
    unittest.main()
