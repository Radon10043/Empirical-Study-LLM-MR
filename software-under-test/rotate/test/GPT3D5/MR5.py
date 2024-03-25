from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(load_test_cases)
    def test5(self, img: np.array, angle: float):
        """Metamorphic Relation 5: Rotating an image and then rotating the result by the same angle should result in the same output as rotating the original image by 2 times the angle."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out_temp = ndimage.rotate(source_out, angle)  # Rotate the source output by the same angle
        follow_angle = angle * 2

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.array_equal(follow_out, follow_out_temp))


if __name__ == "__main__":
    unittest.main()
