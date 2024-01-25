from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test2(self, img: np.array, angle: float):
        """Metamorphic Relation 2: Rotating the image by angle A, and then by angle B, is equivalent to rotating the image by A+B."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = angle + 30  # or any other angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, 30)

        # Verification
        combined_out = ndimage.rotate(img, angle + 30)
        self.assertTrue(np.array_equal(follow_out, combined_out))


if __name__ == "__main__":
    unittest.main()
