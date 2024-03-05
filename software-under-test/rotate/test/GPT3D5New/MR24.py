from utils import *

# fixed
class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test24(self, img: np.array, angle: float):
        """Metamorphic Relation 24: Rotating the image by 360 degrees should result in the same output as the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = 360 + angle # 360 degrees

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.any(follow_out - source_out) == 0)   # Fixed


if __name__ == "__main__":
    unittest.main()
