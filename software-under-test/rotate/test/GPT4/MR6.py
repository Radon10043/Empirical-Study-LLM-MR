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
    def test_rotate_axes(self, img: np.array, angle: float, axes: tuple):
        """Metamorphic Relation 6: Rotating an image by angle N around different pairs of axes and then by angle -N should not yield the same result if axes are different."""
        # Get source output around original set of axes
        source_out = ndimage.rotate(img, angle, axes=axes)

        # Get follow-up output by rotating back around swapped set of axes
        swapped_axes = (axes[1], axes[0])
        follow_out = ndimage.rotate(source_out, -angle, axes=swapped_axes)

        # Verification
        if axes != swapped_axes:
            with self.assertRaises(AssertionError):
                np.testing.assert_array_almost_equal(follow_out, img)


if __name__ == "__main__":
    unittest.main()
