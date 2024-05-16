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
    def test_rotate_identical_with_different_orders(self, img: np.array, angle: float):
        """Metamorphic Relation 8: Rotating an image by the same angle but with different interpolation orders may not yield the same result."""
        # Get source output with default order
        source_out_default_order = ndimage.rotate(img, angle)

        # Get follow-up output with a different order (order=1 in this case, could be other valid orders)
        follow_out_different_order = ndimage.rotate(img, angle, order=1)

        # Verification that images are not exactly the same due to order difference
        with self.assertRaises(AssertionError):
            np.testing.assert_array_almost_equal(source_out_default_order, follow_out_different_order)


if __name__ == "__main__":
    unittest.main()
