from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test32(self, img: np.array, angle: float):
        """Metamorphic Relation 32: Rotating the image by angle A and then translating the resulting image is equivalent to translating the original image and then rotating the result by angle A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        tx = 10  # translation in x-axis
        ty = 20  # translation in y-axis
        follow_out = ndimage.shift(source_out, (tx, ty))

        # Verification
        translated_source_out = ndimage.shift(img, (tx, ty))
        rotated_translated_out = ndimage.rotate(translated_source_out, angle)
        self.assertTrue(np.array_equal(follow_out, rotated_translated_out))


if __name__ == "__main__":
    unittest.main()
