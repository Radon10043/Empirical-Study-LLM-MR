from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test4(self, img: np.array, angle: float):
        """Metamorphic Relation 4: Rotating a horizontally flipped image by a certain angle is equivalent to the same rotation applied to the original image and then horizontally flipping the result."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        flipped_img = np.fliplr(img)

        # Get follow-up output
        follow_out = ndimage.rotate(flipped_img, angle)

        # Verification
        flipped_source_out = np.fliplr(source_out)
        self.assertTrue(np.array_equal(follow_out, flipped_source_out))


if __name__ == "__main__":
    unittest.main()
