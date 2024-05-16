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
    def test_rotate_with_mode(self, img: np.array, angle: float):
        """Metamorphic Relation 10: Rotating an image by any angle with different modes should change the pixels outside the original boundaries."""
        # Get source output with constant mode
        source_out_constant_mode = ndimage.rotate(img, angle, mode="constant")

        # Get follow-up output with wrap mode
        follow_out_wrap_mode = ndimage.rotate(img, angle, mode="wrap")

        # Verification: Check that the pixels that lie outside the initial boundaries are not equal
        boundary_mask = np.logical_or(source_out_constant_mode == 0, follow_out_wrap_mode == 0)
        with self.assertRaises(AssertionError):
            np.testing.assert_array_almost_equal(source_out_constant_mode[boundary_mask], follow_out_wrap_mode[boundary_mask])


if __name__ == "__main__":
    unittest.main()
