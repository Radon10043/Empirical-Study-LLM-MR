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
    def test_rotate_scale_up_down(self, img: np.array, angle: float, scale_factor: float):
        """Metamorphic Relation 9: Scale up and then rotating an image should be equivalent to rotating and then scaling up the image."""
        # Scale up the image
        zoomed_img = ndimage.zoom(img, scale_factor)

        # Get source output: rotate after scaling
        source_rotate_after_scaling = ndimage.rotate(zoomed_img, angle)

        # Get follow-up output: scale after rotating
        rotate_first_then_scale = ndimage.zoom(ndimage.rotate(img, angle), scale_factor)

        # Verification
        np.testing.assert_array_almost_equal(source_rotate_after_scaling, rotate_first_then_scale)


if __name__ == "__main__":
    unittest.main()
