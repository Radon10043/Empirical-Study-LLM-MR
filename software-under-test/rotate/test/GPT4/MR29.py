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
    def test_rotate_and_resize(self, img: np.array, angle: float, axes: tuple, scale_factor: float):
        """Metamorphic Relation 29: Rotating and then resizing an image should be equivalent to resizing first and then rotating."""
        # Rotate and then resize the rotated image
        rotated_img = ndimage.rotate(img, angle, axes=axes, reshape=True)
        resized_after_rotate = ndimage.zoom(rotated_img, scale_factor)

        # Resize and then rotate the resized image
        resized_img = ndimage.zoom(img, scale_factor)
        rotated_after_resize = ndimage.rotate(resized_img, angle, axes=axes, reshape=True)

        # Verification
        np.testing.assert_array_almost_equal(resized_after_rotate, rotated_after_resize)


if __name__ == "__main__":
    unittest.main()
