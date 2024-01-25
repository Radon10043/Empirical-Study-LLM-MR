from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test18(self, img: np.array, angle: float):
        """Metamorphic Relation 18: Rotating the image by angle A and then rotating the resulting image by angle B is equivalent to rotating the original image by angle B and then rotating the result by angle A+B."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct combined rotation angle
        combined_angle = angle + 30  # or any other angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, 30)
        combined_out = ndimage.rotate(img, combined_angle)

        # Verification
        self.assertTrue(np.array_equal(follow_out, combined_out))


if __name__ == "__main__":
    unittest.main()
