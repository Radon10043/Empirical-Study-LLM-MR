from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test5(self, img: np.array, angle: float):
        """Metamorphic Relation 5: Rotating an image by angle A, and then rotating the same image by angle -A, will return the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = -angle

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, follow_angle)

        # Verification
        self.assertTrue(np.array_equal(follow_out, img))


if __name__ == "__main__":
    unittest.main()
