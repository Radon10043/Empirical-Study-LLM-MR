from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test39(self, img: np.array, angle: float):
        """Metamorphic Relation 39: Rotating an image and the result by the same angle will yield the same output as the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Get follow-up output
        follow_out = ndimage.rotate(source_out, angle)

        # Verification
        self.assertTrue(np.all(follow_out - img) == 0)

if __name__ == "__main__":
    unittest.main()
