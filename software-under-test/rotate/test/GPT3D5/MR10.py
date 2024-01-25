from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test10(self, img: np.array, angle: float):
        """Metamorphic Relation 10: Rotating the image by angle A and then rotating the resulting image by angle B is equivalent to rotating the original image by angle B and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = 30  # or any other angle
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        rotated_img = ndimage.rotate(img, follow_angle)
        rotated_out = ndimage.rotate(rotated_img, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_out))


if __name__ == "__main__":
    unittest.main()
