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
    def test_rotate_output_shape(self, img: np.array, angle: float):
        """Metamorphic Relation 33: The shape of the output of a rotated image should either match the input or be larger when reshape is True."""
        # Rotate with reshape=True
        rotated_img = ndimage.rotate(img, angle, reshape=True)

        # Verification: The output dimensions should be greater than or equal to the original
        assert all(s <= rs for s, rs in zip(img.shape, rotated_img.shape))


if __name__ == "__main__":
    unittest.main()
