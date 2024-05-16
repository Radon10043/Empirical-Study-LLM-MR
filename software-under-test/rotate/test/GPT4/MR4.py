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
    def test_rotate_opposite_angles(self, img: np.array, angle: float):
        """Metamorphic Relation 4: Rotating an image by angle N and then by angle -N should yield the same result as the original."""
        # Get source output
        once_rotated = ndimage.rotate(img, angle)

        # Construct follow-up input
        opposite_angle = -angle

        # Get follow-up output
        back_rotated = ndimage.rotate(once_rotated, opposite_angle)

        # Verification
        np.testing.assert_array_almost_equal(back_rotated, img)


if __name__ == "__main__":
    unittest.main()
