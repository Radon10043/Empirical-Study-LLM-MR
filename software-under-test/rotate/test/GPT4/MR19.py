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
    def test_rotate_by_90_degrees(self, img: np.array):
        """Metamorphic Relation 19: Rotating an image by 90 degrees four times should return to the original image."""
        rotated_img = img.copy()
        for _ in range(4):
            rotated_img = ndimage.rotate(rotated_img, 90, reshape=False)

        # Verification
        np.testing.assert_array_almost_equal(rotated_img, img)


if __name__ == "__main__":
    unittest.main()
