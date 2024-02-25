from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(load_test_cases)
    def test3(self, img: np.array, angle: float):
        """Metamorphic Relation 3: Rotating the image by 360-degree multiples of a specific angle will result in the same output."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        # follow_angle = angle * n  # where n is an integer
        follow_angle = angle + 360 * 2  # where n is an integer

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.all(follow_out - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
