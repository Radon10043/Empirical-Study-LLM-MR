from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test13(self, img: np.array, angle: float):
        """Metamorphic Relation 13: Rotating the image by angle A and then applying median filtering is equivalent to applying median filtering to the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.median_filter(source_out, size=3)  # or any other filter size

        # Verification
        median_source_out = ndimage.median_filter(img, size=3)
        rotated_median_out = ndimage.rotate(median_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_median_out))


if __name__ == "__main__":
    unittest.main()
