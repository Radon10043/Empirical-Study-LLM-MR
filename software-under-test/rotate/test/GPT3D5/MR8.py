from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test8(self, img: np.array, angle: float):
        """Metamorphic Relation 8: Rotating the image by angle A and scaling the result by a factor of B is equivalent to scaling the original image by factor B and then rotating the result by angle B*A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        scale_factor = 0.5  # or any other scale factor
        follow_img = ndimage.zoom(img, scale_factor)

        # Get follow-up output
        follow_out = ndimage.rotate(follow_img, angle*scale_factor)

        # Verification
        scaled_source_out = ndimage.zoom(source_out, scale_factor)
        self.assertTrue(np.array_equal(follow_out, scaled_source_out))


if __name__ == "__main__":
    unittest.main()
