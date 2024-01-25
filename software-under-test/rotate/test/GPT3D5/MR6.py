from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test6(self, img: np.array, angle: float):
        """Metamorphic Relation 6: Rotating the image by 0 degree will return the original image."""
        # Get source output
        source_out = ndimage.rotate(img, 0)

        # Verification
        self.assertTrue(np.array_equal(source_out, img))


if __name__ == "__main__":
    unittest.main()
