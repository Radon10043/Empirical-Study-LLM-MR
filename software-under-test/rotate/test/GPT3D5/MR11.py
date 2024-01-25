from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test11(self, img: np.array, angle: float):
        """Metamorphic Relation 11: Rotating the image by angle A and then cropping the resulting image is equivalent to cropping the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        cropped_img = img[50:150, 50:150]  # or any other cropping dimensions
        follow_out = ndimage.rotate(cropped_img, angle)

        # Verification
        croppd_source_out = source_out[50:150, 50:150]
        self.assertTrue(np.array_equal(follow_out, croppd_source_out))


if __name__ == "__main__":
    unittest.main()
