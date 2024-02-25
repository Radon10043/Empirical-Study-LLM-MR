from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test40(self, img: np.array, angle: float):
        """Metamorphic Relation 40: Rotating an image by angle and then rotating the result with a negative angle should yield the same output as the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = -angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        self.assertTrue(np.all(follow_out - img) == 0)


if __name__ == "__main__":
    unittest.main()
