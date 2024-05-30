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
    def test_rotate_half_turn(self, img: np.array, angle: float):   # Fixed
        """Metamorphic Relation 40: Rotating an image by 180 degrees twice should result in the original image."""
        # Apply a 180-degree rotation two times
        rotated_img = ndimage.rotate(ndimage.rotate(img, 180, reshape=False), 180, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(rotated_img, img)


if __name__ == "__main__":
    unittest.main()
