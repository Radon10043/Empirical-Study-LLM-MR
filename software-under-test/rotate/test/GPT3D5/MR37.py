from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test37(self, img: np.array, angle: float):
        """Metamorphic Relation 37: Rotating the image by angle A and then applying a laplace filter to the resulting image is equivalent to applying the laplace filter to the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.laplace(source_out)

        # Verification
        laplace_source_out = ndimage.laplace(img)
        rotated_laplace_out = ndimage.rotate(laplace_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_laplace_out))


if __name__ == "__main__":
    unittest.main()
