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
    def test_rotate_reshape_true_then_false(self, img: np.array, angle: float):
        """Metamorphic Relation 25: Rotating an image with reshape=True and then reshape=False should differ when angle leads to non-square reshaping."""
        # Rotate with reshape=True, allowing image size alteration
        rotated_reshape_true = ndimage.rotate(img, angle, reshape=True)

        # Rotate with reshape=False, forcing image size retention
        rotated_reshape_false = ndimage.rotate(img, angle, reshape=False)

        # Verification: If angle is such that the image shape alters, the results should differ
        if angle % 90 != 0:
            with self.assertRaises(AssertionError):
                np.testing.assert_array_equal(rotated_reshape_true, rotated_reshape_false)
        else:
            # For multiples of 90 degrees, the shape is square and the result should be similar
            np.testing.assert_array_almost_equal(rotated_reshape_true, rotated_reshape_false)


if __name__ == "__main__":
    unittest.main()
