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
    def test_rotate_opposite(self, img: np.array, angle: float):
        """Metamorphic Relation 23: Rotating an image by angle A and then by -A should return identical images if subsequent rotation does not include prefiltering."""
        # Rotate by angle A
        rotated_img_a = ndimage.rotate(img, angle, prefilter=True)

        # Rotate by angle -A without prefiltering
        restored_img = ndimage.rotate(rotated_img_a, -angle, prefilter=False)

        # Verification
        np.testing.assert_array_almost_equal(restored_img, img)


if __name__ == "__main__":
    unittest.main()
