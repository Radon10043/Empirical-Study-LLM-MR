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
    def test_rotate_360(self, img: np.array, angle: float):   # Fixed
        """Metamorphic Relation 1: Rotating the same image by 0 degree and 360 degrees should yield the same result."""
        # Get source output
        source_out = ndimage.rotate(img, 0)

        # Construct follow-up input
        follow_angle = 360

        # Get follow-up output
        follow_out = ndimage.rotate(img, follow_angle)

        # Verification
        np.testing.assert_array_almost_equal(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
