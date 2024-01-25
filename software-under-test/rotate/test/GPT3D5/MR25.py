from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test25(self, img: np.array, angle: float):
        """Metamorphic Relation 25: Rotating the image by angle A and then applying a maximum filter to the resulting image is equivalent to applying the maximum filter to the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.maximum_filter(source_out, size=3)  # or any other filter size

        # Verification
        maximum_source_out = ndimage.maximum_filter(img, size=3)
        rotated_maximum_out = ndimage.rotate(maximum_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_maximum_out))


if __name__ == "__main__":
    unittest.main()
