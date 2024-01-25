from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test12(self, img: np.array, angle: float):
        """Metamorphic Relation 12: Rotating the image by angle A and then applying a Gaussian filter to the resulting image is equivalent to applying the Gaussian filter to the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.gaussian_filter(source_out, sigma=1)  # or any other sigma value

        # Verification
        gaussian_source_out = ndimage.gaussian_filter(img, sigma=1)
        rotated_gaussian_out = ndimage.rotate(gaussian_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_gaussian_out))


if __name__ == "__main__":
    unittest.main()
