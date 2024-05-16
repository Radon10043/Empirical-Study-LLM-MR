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
    def test_rotate_transpose_equivalence(self, img: np.array, angle: float):
        """Metamorphic Relation 26: For 2D images, rotating by 90 degrees clockwise (negative angle) should be equivalent to a transpose operation."""
        # Rotate by -90 degrees (clockwise)
        rotated_img_cw_90 = ndimage.rotate(img, -90, reshape=False)

        # Transpose (equivalent to a 90-degree clockwise rotation)
        transposed_img = np.transpose(img)

        # Verification
        np.testing.assert_array_almost_equal(rotated_img_cw_90, transposed_img)


if __name__ == "__main__":
    unittest.main()
