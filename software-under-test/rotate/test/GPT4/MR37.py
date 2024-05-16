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
    def test_rotate_compare_order_effects(self, img: np.array, angle: float):
        """Metamorphic Relation 37: Using different spline interpolation orders during rotation can affect the image's quality but not the overall structure."""
        orders = [0, 1, 2, 3, 4, 5]

        # Rotate with order 0 (nearest neighbor)
        rotated_img_order_0 = ndimage.rotate(img, angle, reshape=False, order=orders[0])

        for order in orders[1:]:
            # Rotate with higher order
            rotated_img_higher_order = ndimage.rotate(img, angle, reshape=False, order=order)

            # Calculate the difference
            diff = rotated_img_higher_order.astype("float32") - rotated_img_order_0.astype("float32")

            # Verify that the difference mostly occurs at pixel-level, not structural level
            # i.e., the difference image should not have large connected components
            labeled_diff, num_features = ndimage.label(diff > 1e-1)  # Label regions with significant difference
            assert num_features < 5  # Arbitrary threshold assuming no major structural changes


if __name__ == "__main__":
    unittest.main()
