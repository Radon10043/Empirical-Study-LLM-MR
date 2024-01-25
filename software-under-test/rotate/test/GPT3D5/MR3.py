from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test3(self, img: np.array, angle: float):
        """Metamorphic Relation 3: Rotating the image by angle A, and then rotating the resulting image by angle B, is equivalent to rotating the original image by angle A+B."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = 30  # or any other angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        combined_out = ndimage.rotate(img, angle + follow_angle)
        self.assertTrue(np.array_equal(follow_out, combined_out))


if __name__ == "__main__":
    unittest.main()
