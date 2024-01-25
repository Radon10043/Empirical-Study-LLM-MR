from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test15(self, img: np.array, angle: float):
        """Metamorphic Relation 15: Rotating the image by angle A and then flipping the resulting image horizontally is equivalent to flipping the original image horizontally and then rotating the result by angle -A."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = np.fliplr(source_out)

        # Verification
        flipped_source = np.fliplr(img)
        rotated_flipped_out = ndimage.rotate(flipped_source, -angle)
        self.assertTrue(np.array_equal(follow_out, rotated_flipped_out))


if __name__ == "__main__":
    unittest.main()
