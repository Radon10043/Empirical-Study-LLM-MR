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
    def test_rotate_reshape_false(self, img: np.array, angle: float):
        """Metamorphic Relation 5: When reshape is False, rotating an image by 0 degree and any angle should have same dimensions."""
        # Get source output
        source_out = ndimage.rotate(img, 0, reshape=False)

        # Get follow-up output with reshape=False
        follow_out = ndimage.rotate(img, angle, reshape=False)

        # Verification for shape
        assert source_out.shape == follow_out.shape


if __name__ == "__main__":
    unittest.main()
