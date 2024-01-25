from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test22(self, img: np.array, angle: float):
        """Metamorphic Relation 22: Rotating the image by angle A and then applying a uniform filter to the resulting image is equivalent to applying the uniform filter to the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.uniform_filter(source_out, size=3)  # or any other filter size

        # Verification
        uniform_source_out = ndimage.uniform_filter(img, size=3)
        rotated_uniform_out = ndimage.rotate(uniform_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_uniform_out))


if __name__ == "__main__":
    unittest.main()
