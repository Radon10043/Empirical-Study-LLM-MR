from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test34(self, img: np.array, angle: float):
        """Metamorphic Relation 34: Rotating an image and then rotating the result by 180 degrees should result in the original image."""
        # Get source output
        source_out = ndimage.rotate(img, angle)

        # Construct follow-up input
        follow_out = ndimage.rotate(source_out, 180)  # Rotate the result by 180 degrees

        # Verification
        self.assertTrue(np.all(follow_out - img) == 0)



if __name__ == "__main__":
    unittest.main()
