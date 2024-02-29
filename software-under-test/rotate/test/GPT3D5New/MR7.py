from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test7(self, img: np.array, angle: float):
        """Metamorphic Relation 7: Rotating the image by 0 degrees should result in the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = 0  # 0 degrees

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        self.assertTrue(np.all(follow_out - img) == 0)


if __name__ == "__main__":
    unittest.main()
