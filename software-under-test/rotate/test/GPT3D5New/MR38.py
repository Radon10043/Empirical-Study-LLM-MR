from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test38(self, img: np.array, angle: float):
        """Metamorphic Relation 38: Rotating the same image by N degree and N+360 degree should output the same result."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = angle + 360

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.all(follow_out - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
