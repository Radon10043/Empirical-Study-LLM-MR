from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test9(self, img: np.array, angle: float):
        """Metamorphic Relation 9: Rotating the image by angle A and then scaling the resulting image by a factor of B is equivalent to scaling the original image by factor B and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        scale_factor = 0.5  # or any other scale factor
        follow_out = ndimage.zoom(source_out, scale_factor)

        # Verification
        rotated_scaled_img = ndimage.zoom(img, scale_factor)
        rotated_scaled_out = ndimage.rotate(rotated_scaled_img, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_scaled_out))


if __name__ == "__main__":
    unittest.main()
