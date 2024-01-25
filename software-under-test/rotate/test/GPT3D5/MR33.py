from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test33(self, img: np.array, angle: float):
        """Metamorphic Relation 33: Rotating the image by angle A and then rotating the resulting image by the same angle in the opposite direction is equivalent to the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = -angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        self.assertTrue(np.array_equal(follow_out, img))


if __name__ == "__main__":
    unittest.main()
