import os
import sys
import unittest

import numpy as np
from scipy import ndimage, datasets
from parameterized import parameterized

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test_rotate_multiple_of_180_degrees(self, img: np.array):
        """Metamorphic Relation 27: Rotating an image by any angle that is a multiple of 180 degrees should result in either the same or upside-down image."""
        for multiple in [1, 2, 3, 4]:
            angle = 180 * multiple
            rotated_img = ndimage.rotate(img, angle, reshape=False)

            # When the multiple is odd, we expect the image to be upside down
            expected_img = img if multiple % 2 == 0 else np.flip(np.flip(img, axis=0), axis=1)

            # Verification
            np.testing.assert_array_almost_equal(rotated_img, expected_img)


if __name__ == "__main__":
    unittest.main()
