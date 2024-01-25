from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test24(self, img: np.array, angle: float):
        """Metamorphic Relation 24: Rotating the image by angle A and then performing edge detection is equivalent to performing edge detection on the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.sobel(source_out)

        # Verification
        sobel_source_out = ndimage.sobel(img)
        rotated_sobel_out = ndimage.rotate(sobel_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_sobel_out))


if __name__ == "__main__":
    unittest.main()
