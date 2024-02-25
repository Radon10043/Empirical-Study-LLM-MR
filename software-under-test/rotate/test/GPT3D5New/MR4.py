from utils import *


class TestingClass(unittest.TestCase):
    # fixed
    @parameterized.expand(load_test_cases)
    def test4(self, img: np.array, angle: float):
        """Metamorphic Relation 4: Rotating the image by 90-degree multiples will result in the same output up to a permutation of axes."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_angle = angle + 90  # where 90 is a multiple of 90 degrees

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Transpose follow_out to match the shape of source_out
        permuted_follow_out = np.transpose(follow_out, axes=(2, 0, 1))

        # Verification
        self.assertTrue(np.all(np.transpose(permuted_follow_out) - source_out) == 0)


if __name__ == "__main__":
    unittest.main()
