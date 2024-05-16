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
    def test_rotate_additive_angles(self, img: np.array, angle1: float, angle2: float):
        """Metamorphic Relation 7: Rotating an image consecutively by angle A and angle B should be the same as rotating it once by angle A+B."""
        # Get source output
        first_rotate_out = ndimage.rotate(img, angle1)

        # Get intermediate output by rotating by angle2
        second_rotate_out = ndimage.rotate(first_rotate_out, angle2)

        # Get expected output by rotating once by angle1+angle2
        combined_rotate_out = ndimage.rotate(img, angle1 + angle2)

        # Verification
        np.testing.assert_array_almost_equal(second_rotate_out, combined_rotate_out)


if __name__ == "__main__":
    unittest.main()
