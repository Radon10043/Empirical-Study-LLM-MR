from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test28(self, img: np.array, angle: float):
        """Metamorphic Relation 28: Rotating the image by angle A and then blurring the resulting image is equivalent to blurring the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.gaussian_filter(source_out, sigma=1.5)  # or any other sigma value

        # Verification
        blurred_source_out = ndimage.gaussian_filter(img, sigma=1.5)
        rotated_blurred_out = ndimage.rotate(blurred_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_blurred_out))


if __name__ == "__main__":
    unittest.main()
