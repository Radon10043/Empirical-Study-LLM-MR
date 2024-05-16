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
    def test_rotate_prefilter_false(self, img: np.array, angle: float):
        """Metamorphic Relation 18: Rotating an image with prefilter False may result in differences compared to default rotation due to lack of spline filtering."""
        # Rotate the image with prefilter set to True
        rotated_prefilter_true = ndimage.rotate(img, angle)

        # Rotate the image with prefilter set to False
        rotated_prefilter_false = ndimage.rotate(img, angle, prefilter=False)

        # Verification: Check that the images might not be exactly equal due to lack of prefiltering
        with self.assertRaises(AssertionError):
            np.testing.assert_array_almost_equal(rotated_prefilter_true, rotated_prefilter_false)


if __name__ == "__main__":
    unittest.main()
