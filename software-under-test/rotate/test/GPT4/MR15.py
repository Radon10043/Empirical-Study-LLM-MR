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
    def test_rotate_then_inverse(self, img: np.array, angle: float):
        """Metamorphic Relation 15: Rotating an image by angle A and then by -A should return to the original image if reshape=False."""
        # Rotate by angle A
        rotate_by_a = ndimage.rotate(img, angle, reshape=False)

        # Rotate the result by -A to attempt to recover the original image
        rotate_by_inverse_a = ndimage.rotate(rotate_by_a, -angle, reshape=False)

        # Verification: Expect the recovered image to be close to the original image
        np.testing.assert_array_almost_equal(rotate_by_inverse_a, img)


if __name__ == "__main__":
    unittest.main()
