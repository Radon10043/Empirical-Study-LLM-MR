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
    def test_rotate_identity(self, img: np.array):
        """Metamorphic Relation 22: Rotating an image by 0 degrees should return the identical image."""
        rotated_img = ndimage.rotate(img, 0)

        # Verification
        np.testing.assert_array_equal(rotated_img, img)


if __name__ == "__main__":
    unittest.main()
