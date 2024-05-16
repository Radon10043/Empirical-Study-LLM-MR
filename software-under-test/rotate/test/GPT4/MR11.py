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
    def test_rotate_different_cval(self, img: np.array, angle: float):  # Fixed
        """Metamorphic Relation 11: Rotating an image with two different 'cval' values should change the fill values in the output."""
        # Ensure different cval values
        cval1 = 1.0
        cval2 = 2.0

        # Get source output with cval1
        source_out_cval1 = ndimage.rotate(img, angle, cval=cval1)

        # Get follow-up output with cval2
        follow_out_cval2 = ndimage.rotate(img, angle, cval=cval2)

        # Verification: Check that the filled values are different
        filled_pixels_cval1 = source_out_cval1[source_out_cval1 == cval1]
        filled_pixels_cval2 = follow_out_cval2[follow_out_cval2 == cval2]
        with self.assertRaises(AssertionError):
            np.testing.assert_array_equal(filled_pixels_cval1, filled_pixels_cval2)


if __name__ == "__main__":
    unittest.main()
